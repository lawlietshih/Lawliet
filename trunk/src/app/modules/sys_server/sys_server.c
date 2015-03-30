#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <sys/prctl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/select.h>

#include <sys/wait.h>
#include <sys/epoll.h>

#include "../../../../include/prj_types.h"
#include "../../include/app_common.h"
#include "../../../../utility/include/utility.h"

int syssrv_run = 1;

void Init_System_Server(void)
{
	PTHREAD       pid;
	PTHREADATTR   attr;

	PTHREAD_ATTR_INIT(&attr);
	PTHREAD_ATTR_SETDETACHSTATE(&attr,PTHREAD_CREATE_DETACHED);
	PTHREAD_CREATE(&pid, &attr, SysSrvThread, NULL);
	PTHREAD_ATTR_DESTROY(&attr);
}

void Destroy_System_Server(void)
{
	syssrv_run = 0;

	struct sockaddr_in server_addr;
	char send_buf[16];
	S32 net_server_socket = -1;
	int one = 1;

	LDBG("destroy system server....\r\n");
	//runCmdServer = 2;
	
	sprintf(send_buf,"QUIT:LAWLIET");
	if((net_server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
		LDBG("destroy system server socket error!\r\n");
		return;
	}
	
	if(setsockopt(net_server_socket, SOL_SOCKET, SO_REUSEADDR, (char*) &one, sizeof(one)) == -1){
		LDBG("destroy system server setsockopt error!\r\n");
		_SAFE_CLOSE(net_server_socket);
		return;
	}

	if (setsockopt(net_server_socket, SOL_SOCKET, SO_REUSEPORT, (char*)&one, sizeof(one)) == -1){
		LDBG("setsockopt error!\r\n");
		_SAFE_CLOSE(net_server_socket);
		return;
	}

	bzero(&server_addr,sizeof(server_addr));
 	server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SYS_SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	if(connect(net_server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		_SAFE_CLOSE(net_server_socket);
		LDBG("Connect to cmd_net_server error!!\r\n");
		return;
	}

	writen(net_server_socket, send_buf, strlen(send_buf));
	_SAFE_CLOSE(net_server_socket);
}

void *SysSrvThread(void *p)
{
	int SysSrvSocket = -1; 
	int on = 1;
	int segSize= 1200;//TCP Maximum Segment Size (MSS) 
	int opt_value = 1;
	struct timeval timeout;
	struct linger so_linger;
	int sendBufSize = 512 * 1024;//512K
	int recvBufSize = 512 * 1024;//512K
	int flags;
	struct sockaddr_in server_addr;

	int SysSrvEpoll  = -1;
	struct epoll_event event;
  	struct epoll_event *events;
	struct sockaddr client_addr;
    socklen_t client_len;
    int ClientSocket = -1;
	
	/* TCP socket : create */
	if((SysSrvSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		LDBG("socket error!\r\n");
		return NULL;
	}

	/* socket option */
	if(setsockopt(SysSrvSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) == -1){
		LDBG("setsockopt error!\r\n");
		_SAFE_CLOSE(SysSrvSocket);
		//print_errno();
		return NULL;
	}

	if(setsockopt(SysSrvSocket, SOL_SOCKET, SO_REUSEPORT, (char*)&on, sizeof(on)) == -1){
		LDBG("setsockopt error!\r\n");
		_SAFE_CLOSE(SysSrvSocket);
		//print_errno();
		return NULL;
	}

	so_linger.l_onoff = 1;
	so_linger.l_linger = 0;
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	setsockopt(SysSrvSocket, IPPROTO_TCP, TCP_MAXSEG,  (int*)&segSize,     sizeof(segSize));
	setsockopt(SysSrvSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&opt_value,  sizeof(opt_value));
	setsockopt(SysSrvSocket, SOL_SOCKET,  SO_SNDTIMEO, (char*)&timeout,    sizeof(timeout));
	setsockopt(SysSrvSocket, SOL_SOCKET,  SO_RCVTIMEO, (char*)&timeout,    sizeof(timeout));
	setsockopt(SysSrvSocket, SOL_SOCKET,  SO_SNDBUF,   (int*)&sendBufSize, sizeof(sendBufSize));
	setsockopt(SysSrvSocket, SOL_SOCKET,  SO_RCVBUF,   (int*)&recvBufSize, sizeof(recvBufSize));
	setsockopt(SysSrvSocket, SOL_SOCKET,  SO_LINGER,   &so_linger,         sizeof(so_linger));

	/* server socket mode */
	if((flags = fcntl(SysSrvSocket, F_GETFL, 0)) == -1){
		LDBG("fcntl F_GETFL error!!\r\n");
	}

#if 0
	flags &= ~O_NONBLOCK;//blocking
#else
	flags |= O_NONBLOCK;//non-blocking
#endif

	if((fcntl(SysSrvSocket, F_SETFL, flags)) == -1){
		LDBG("fcntl F_SETFL error!!\r\n");
	}

	/* server address */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET ;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr(MEDIA_SERVER_IP)
	server_addr.sin_port = htons(SYS_SERVER_PORT);

	/* TCP socket : bind & listen */
	if(bind(SysSrvSocket, (struct sockaddr *) &server_addr , sizeof(server_addr)) == -1){
		LDBG("SysSrvSocket bind failed\r\n");
		_SAFE_CLOSE(SysSrvSocket);
	}
	
	if(listen(SysSrvSocket, MAX_CFG_SERVER_LISTEN_QUEUE) == -1){//system backlog : SOMAXCONN
		LDBG("SysSrvSocket listen failed\r\n");
	}

	/* epoll or select */
	if((SysSrvEpoll = epoll_create1(0)) == -1){
		LDBG("SysSrvEpoll create failed\r\n");
	}

	event.data.fd = SysSrvSocket;
  	event.events = EPOLLIN | EPOLLET;

	if(epoll_ctl(SysSrvEpoll, EPOLL_CTL_ADD, SysSrvSocket, &event) == -1){
		LDBG("SysSrvEpoll control failed\r\n");
	}

	/* Buffer where events are returned */
  	events = calloc (MAXEVENTS, sizeof event);
	
	while(syssrv_run){
		int n, i;
 		LDBG("sys_server epoll_wait... !\n");
      	n = epoll_wait(SysSrvEpoll, events, MAXEVENTS, -1);
		//LDBG("n : %d\n", n);//n == 1
		
		for (i=0; i<n; i++){
			if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN))){
				LDBG ("SysSrvEpoll error\n");
          		_SAFE_CLOSE (events[i].data.fd);
          		continue;
			}else if(SysSrvSocket == events[i].data.fd){
                client_len = sizeof(client_addr);
				/* TCP socket : accept */
                ClientSocket = accept(SysSrvSocket, &client_addr, &client_len);
				//LDBG("ClientSocket : %d\n", ClientSocket);
				  
				if(ClientSocket < 0)
				{
					LDBG("ClientSocket accept failed !\n");
					break;
				}

				LDBG("sys_server accept a client : success !\n");

				/* client socket mode */
				if((flags = fcntl(ClientSocket, F_GETFL, 0)) == -1){
					LDBG("fcntl F_GETFL error!!\r\n");
				}

				flags |= O_NONBLOCK;//non-blocking

				if((fcntl(ClientSocket, F_SETFL, flags)) == -1){
					LDBG("fcntl F_SETFL error!!\r\n");
				}

				/* epoll or select */
				event.data.fd = ClientSocket;
  				event.events = EPOLLIN | EPOLLET;

				if(epoll_ctl(SysSrvEpoll, EPOLL_CTL_ADD, ClientSocket, &event) == -1){
					LDBG("SysSrvEpoll control failed\r\n");
				}
			}else if(events[i].events & EPOLLIN){
				LDBG("Epoll Event : EPOLLIN !\n");
			}else if(events[i].events & EPOLLOUT){
				LDBG("Epoll Event : EPOLLOUT !\n");
			}
		}
		
		LDBG("sys_server live... !\n");
		//sleep(3);
	}

	free(events);
  	_SAFE_CLOSE (SysSrvSocket);

	LDBG("System Server 881... !\n");
	
	return NULL;
}
