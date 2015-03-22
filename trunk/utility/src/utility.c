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
