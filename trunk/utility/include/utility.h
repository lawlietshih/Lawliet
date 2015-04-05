#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <errno.h>
#include "../../include/prj_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define _SAFE_FREE(p)			do { if(p)	{free(p);   p = NULL;} } while(0)
#define _SAFE_FCLOSE(p)			do { if(p)	{fclose(p); p = NULL;} } while(0)
#define _SAFE_CLOSE(p)			do { if(p>0){close(p);  p = -1;}   } while(0)

#define Chk_Flg(a, b) ((a) & (1 << b))
#define Set_Flg(a, b) ((a) |= (1 << b))
#define Clr_Flg(a, b) ((a) &= (~(1 << b)))

int readn(int fd, void *vptr, int n);
int writen(int fd, const void *vptr, int n);

void print_errno(int err_no);

void Lawliet_Set_Flg(unsigned char a, unsigned char b);
void Lawliet_Clear_Flg(unsigned char a, unsigned char b);

int Lawliet_Check_CPUendian(void);

#ifdef __cplusplus
}
#endif

#endif /* _UTILITY_H_ */
