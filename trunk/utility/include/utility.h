#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "../../include/prj_common.h"

#define Chk_Flg(a, b) ((a) & (1 << b))
#define Set_Flg(a, b) ((a) |= (1 << b))
#define Clr_Flg(a, b) ((a) &= (~(1 << b)))

void Lawliet_Set_Flg(unsigned char a, unsigned char b);

void Lawliet_Clear_Flg(unsigned char a, unsigned char b);

#endif /* _UTILITY_H_ */
