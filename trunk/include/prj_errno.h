#ifndef _PRJ_ERRNO_H_
#define _PRJ_ERRNO_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	/* system retval */
	PRJ_ERROR			= -1,
	PRJ_OK				= 0,
	PRJ_RET_MAX
} _PRJResult;

typedef int PRJResult;

#ifdef __cplusplus
}
#endif

#endif /* _PRJ_ERRNO_H_ */

