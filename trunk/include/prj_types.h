#ifndef _PRJ_TYPES_H_
#define _PRJ_TYPES_H_

#include <inttypes.h> /* Portable for 64bit */
#include <stdbool.h>
#include "prj_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t		U64;
typedef int64_t			S64;
typedef uint32_t		U32;
typedef int32_t			S32;
typedef uint16_t		U16;
typedef int16_t			S16;
typedef uint8_t			U8;
typedef int8_t			S8;

typedef	uint8_t			BOOL;
typedef	float			FLOAT;
typedef double			DOUBLE;
typedef void			VOID;
typedef pthread_t		PTHREAD;
typedef pthread_attr_t	PTHREADATTR;

#ifdef __cplusplus
}
#endif

#endif /* _PRJ_TYPES_H_ */

