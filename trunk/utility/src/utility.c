#include <errno.h>
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
  union
  {
    unsigned int a;
    unsigned char b; 
  }c;
  c.a = 0x1234;
  return (c.b == 0x12) ? CPU_BIG_ENDIAN : CPU_LITTLE_ENDIAN;
}

