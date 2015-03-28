#ifndef _PRJ_COMMON_H_
#define _PRJ_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#define CPU_BIG_ENDIAN 	  1
#define CPU_LITTLE_ENDIAN 0

#define LAWLIET_DEBUG	  1
#define LDBG(fmt, ...) do { \
	if(LAWLIET_DEBUG){ \
		fprintf(stderr,"[ Lawliet ]\t" fmt); \
	} \
}while(0)

#if 0		
do { if (LAWLIET_DEBUG)	fprintf(stderr, "[ Lawliet ]\t[%s:%d,%s]\t" fmt, __BASE_FILE__, __LINE__, \
                        (DBG_LEVEL)?__func__:"\b", ##__VA_ARGS__); } while (0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _PRJ_COMMON_H_ */
