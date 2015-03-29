#ifndef _UTILITY_H_
#define _UTILITY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../../include/prj_common.h"

#define Chk_Flg(a, b) ((a) & (1 << b))
#define Set_Flg(a, b) ((a) |= (1 << b))
#define Clr_Flg(a, b) ((a) &= (~(1 << b)))

void Lawliet_Set_Flg(unsigned char a, unsigned char b);

void Lawliet_Clear_Flg(unsigned char a, unsigned char b);

/** 
 * @brief 
 * Check CPU Endian
 * 
 * @param NA
 *
 * @return
 * 1 : Big Endian 
 * 0 : Little Endian
 */
int Lawliet_Check_CPUendian(void);

#ifdef __cplusplus
}
#endif

#endif /* _UTILITY_H_ */
