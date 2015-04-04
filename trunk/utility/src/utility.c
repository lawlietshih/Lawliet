#include "../include/utility.h"

/*
	@socket

	#include <sys/types.h>
	#include <sys/socket.h>
	int socket(int domain, int type, int protocol);

	@param
	
	domain -> AF_xx : Address  Family
		   -> PF_xx : Protocol Family

	type            : Socket   Type
	protocol        : Protocol Type

	---------------------------------------------------------------------

	AF_INET + SOCK_STREAM : TCP
	AF_INET + SOCK_DGRAM  : UDP

	@RAW socket
	send : AF_INET + SOCK_RAW + IPPROTO_ICMP (Layer 3 : IP       Layer)
	send : PF_PACKET/AF_PACKET + SOCK_RAW    (Layer 2 : Ethernet Layer)
	recv : AF_INET + SOCK_RAW
*/

int readn(int fd, void *vptr, int n)
{
	int nleft;
	int nread;
	char *ptr;

	ptr = vptr;
	nleft = n;

	while(nleft > 0)
	{
		LDBG("#readn nleft: %d\n", nleft);
		
		if((nread = read(fd, ptr, nleft)) < 0)
		{
			switch(errno)
			{
				case EAGAIN:// non-blocking : EWOULDBLOCK
				case EINTR:
					/* retry */
					nread = 0;
					print_errno(errno);
					break;
				default :
					/* error */
					print_errno(errno);
					return (-1);
			}
		}else if(nread == 0){
			/* end of buffer */
			break;
		}

		LDBG("#readn nread: %d\n", nread);
		
		nleft -= nread;
		ptr += nread;
	}

	LDBG("#readn (n - nleft): %d\n", (n - nleft));
	return (n - nleft);
}

int writen(int fd, const void *vptr, int n)

{
	int nleft;
	int nwritten;
	const char *ptr;

	ptr = vptr;
	nleft = n;

	while(nleft > 0)
	{
		LDBG("#writen nleft: %d\n", nleft);
		
		if((nwritten = write(fd, ptr, nleft)) <= 0)
		{
			switch(errno)
			{
				case EAGAIN:// non-blocking : EWOULDBLOCK
				case EINTR:
					/* retry */
					nwritten = 0;
					print_errno(errno);
					break;
				default :
					/* error */
					print_errno(errno);
					return (-1);
			}
		}

		LDBG("#writen nwritten: %d\n", nwritten);
		
		nleft -= nwritten;
		ptr += nwritten;
	}

	LDBG("#writen n: %d\n", n);
	
	return n;
}

void print_errno(int err_no){

	switch(err_no)
	{
		case EAGAIN://non-blocking
			/* Resource temporarily unavailable */
			LDBG("EAGAIN\n");
			break;
		//case EWOULDBLOCK://non-blocking
			/* Operation would block */
		//	LDBG("EWOULDBLOCK\t");
		//	break;
		case EINTR:
			/* Interrupted system call */
			LDBG("EINTR\n");
			break;
		default :
			break;
	}

	LDBG("errno %d :\t%s\n", err_no, strerror(err_no));
}

void Lawliet_Set_Flg(unsigned char a, unsigned char b)
{
	if(!Chk_Flg(a, b))
	{
		Set_Flg(a, b);
	}
}

void Lawliet_Clear_Flg(unsigned char a, unsigned char b)
{
	if(Chk_Flg(a, b))
	{
		Clr_Flg(a, b);
	}
}

int Lawliet_Check_CPUendian(void)
{
  /*
  	@Network byte order : Big Endian
  	
  	htons() : host to network short
	htonl() : host to network long
	ntohs() : network to host short
	ntohl() : network to host long

	uint32_t htonl(uint32_t hostlong);
	uint16_t htons(uint16_t hostshort);
	uint32_t ntohl(uint32_t netlong);
	uint16_t ntohs(uint16_t netshort);
  */
  union
  {
    unsigned int a;
    unsigned char b; 
  }c;
  c.a = 0x1234;
  return (c.b == 0x12) ? CPU_BIG_ENDIAN : CPU_LITTLE_ENDIAN;
}

