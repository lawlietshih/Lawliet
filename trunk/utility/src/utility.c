#include "../include/utility.h"

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

