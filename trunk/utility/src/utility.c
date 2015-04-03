#include "../include/utility.h"

int readn(int fd, void *vptr, int n)
{
	int nleft;
	int nread;
	char *ptr;

	ptr = vptr;
	nleft = n;

	while(nleft>0)
	{
		if ((nread = read(fd, ptr, nleft)) < 0)
		{
			if (errno == EINTR)
				nread = 0;
			else
				return (-1);
			/*
			if(errno == EINTER){

			}else if(errno == EAGAIN){

			}
			*/
		}
		else if (nread == 0)
			break;

		nleft -= nread;
		ptr += nread;
	}

	return (n - nleft);
}

int writen(int fd, const void *vptr, int n)

{
	int nleft;
	int nwritten;
	const char *ptr;

	ptr = vptr;
	nleft = n;

	while (nleft > 0)
	{
		if ((nwritten = write(fd, ptr, nleft)) <= 0)
		{
			if (errno == EINTR)
				nwritten = 0;
			else
				return (-1);
		}

		nleft -= nwritten;
		ptr += nwritten;
	}

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

