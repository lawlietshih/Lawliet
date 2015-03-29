#ifndef _APP_COMMON_H_
#define _APP_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../include/prj_common.h"
#include "../../../utility/include/util_thread.h"

void *SysSrvThread(void *p);

void Init_System_Server(void);
void Destroy_System_Server(void);

void Lawliet_APP_Start(void);
void Lawliet_APP_Stop(void);


#ifdef __cplusplus
}
#endif

#endif /* _APP_COMMON_H_ */
