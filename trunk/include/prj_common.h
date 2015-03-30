#ifndef _PRJ_COMMON_H_
#define _PRJ_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Nice LEVEL definitions */
#define NICE_LEVELM20	-20
#define NICE_LEVELM15	-15
#define NICE_LEVELM10	-10
#define NICE_LEVELM5	-5
#define NICE_LEVELM3	-3
#define NICE_LEVELZERO	0
#define NICE_LEVELP5	5
#define NICE_LEVELP10	10
#define NICE_LEVELP15	15
#define NICE_LEVELP19	19

#define MAX_PATH_LENGTH 256
#define ON		1
#define OFF		0
#define KILO 1024llu
#define MEGA (KILO * KILO)
#define GIGA (MEGA * KILO)
#define TERA (GIGA * KILO)

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE !FALSE
#endif

/* Some useful macros */
#define	MEMSET_MALLOC(s)		memset(malloc(s), 0, s)

#define SEC_PER_MIN				(60)
#define SEC_PER_HOUR			(60*60)
#define	SEC_PER_DAY				(60*60*24)
#define	sec_to_day(s)			((s) / SEC_PER_DAY)

#define	is_same_min(s1, s2)		(((s1)/SEC_PER_MIN) == ((s2)/SEC_PER_MIN))
#define	is_same_hour(s1, s2)	(((s1)/SEC_PER_HOUR) == ((s2)/SEC_PER_HOUR))
#define	is_same_day(s1, s2)		(sec_to_day(s1) == sec_to_day(s2))

#define SAFE_FREE(p)		do { if(p)	{free(p);   p = NULL;} } while(0)
#define SAFE_FCLOSE(p)		do { if(p)	{fclose(p); p = NULL;} } while(0)
#define SAFE_CLOSE(p)		do { if(p>0){close(p);  p = -1;}   } while(0)

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) < (b) ? (b): (a))
#endif

#define ATOI(a)			(atoi((const char*)a))

#define msleep(t) usleep(1000 * t)


#define ARRAY_INDEX(index, BitNum) ((index) / (BitNum))

#define BIT_INDEX(index, BitNum) ((index) % (BitNum))


#define CLR_BIT_NUM(addr, index, BitNum, type) \
		*(addr + ARRAY_INDEX(index, BitNum)) &= \
			(~(((type)0x01) << BIT_INDEX(index, BitNum)))

#define SET_BIT_NUM(addr, index, BitNum, type) \
		*(addr + ARRAY_INDEX(index, BitNum)) |= \
			(((type)0x01) << BIT_INDEX(index, BitNum))

#define CHK_BIT_NUM(addr, index, BitNum, type) \
		(*(addr + ARRAY_INDEX(index, BitNum)) >> BIT_INDEX(index, BitNum)) & ((type)0x01)


#define CLR_BIT_BYTE(addr, index) (CLR_BIT_NUM(addr, index, 8, unsigned char))
#define SET_BIT_BYTE(addr, index) (SET_BIT_NUM(addr, index, 8, unsigned char))
#define CHK_BIT_BYTE(addr, index) (CHK_BIT_NUM(addr, index, 8, unsigned char))

#define CLR_BIT_SHORT(addr, index) (CLR_BIT_NUM(addr, index, 16, unsigned short))
#define SET_BIT_SHORT(addr, index) (SET_BIT_NUM(addr, index, 16, unsigned short))
#define CHK_BIT_SHORT(addr, index) (CHK_BIT_NUM(addr, index, 16, unsigned short))

#define CLR_BIT_LL(addr, index) (CLR_BIT_NUM(addr, index, 64, unsigned long long))
#define SET_BIT_LL(addr, index) (SET_BIT_NUM(addr, index, 64, unsigned long long))
#define CHK_BIT_LL(addr, index) (CHK_BIT_NUM(addr, index, 64, unsigned long long))


#define CLR_BIT_LONG(addr, index) (CLR_BIT_NUM(addr, index, 32, unsigned long))
#define SET_BIT_LONG(addr, index) (SET_BIT_NUM(addr, index, 32, unsigned long))
#define CHK_BIT_LONG(addr, index) (CHK_BIT_NUM(addr, index, 32, unsigned long))

#define CLR_BIT_UNINT(addr, index) (CLR_BIT_NUM(addr, index, 32, unsigned int))
#define SET_BIT_UNINT(addr, index) (SET_BIT_NUM(addr, index, 32, unsigned int))
#define CHK_BIT_UNINT(addr, index) (CHK_BIT_NUM(addr, index, 32, unsigned int))

#define CLR_BIT(addr, index) (CLR_BIT_BYTE(addr, index))
#define SET_BIT(addr, index) (SET_BIT_BYTE(addr, index))
#define CHK_BIT(addr, index) (CHK_BIT_BYTE(addr, index))

#define BITS_TO_BYTES(bits) ((bits) + 7) / 8


#define ALIGN_2(num) ((num)&(~0x1))
#define ALIGN_4(n) ((n + 3)/4*4)
#define EDGE_ALIGN(x, align)  ((((x)-1)/(align)+1)*(align))

#define PRJ_RETRIES(f, t, m) \
	do{ \
        int retries = t; \
        int ret; \
        do{ \
			ret = f; \
			retries--; \
		}while(ret < 0 && retries); \
		if (ret < 0) V_ERR(m); \
	}while(0)

#define PRJ_CHECK(f, m) PRJ_RETRIES(f,1, m)


#define CPU_BIG_ENDIAN 	  1
#define CPU_LITTLE_ENDIAN 0

#define LAWLIET_DEBUG	  1

#define LDBG(fmt...) do { \
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
