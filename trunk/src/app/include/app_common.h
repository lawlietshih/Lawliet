#ifndef _APP_COMMON_H_
#define _APP_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../include/prj_common.h"
#include "../../../utility/include/util_thread.h"

#define SYS_SERVER_PORT 7648
#define MAX_CFG_SERVER_LISTEN_QUEUE 1
/* Segment Size : 1. size < 1460 2. Client/Server must be consistent (receive cmd fast) */
#define MAX_SEGSIZE 1200
#define MAXEVENTS 64

#define SERVER_TIMEOUT 1000//ms
#define SYSSRV_TIMEOUT SERVER_TIMEOUT

void *SysSrvThread(void *p);

void Init_System_Server(void);
void Destroy_System_Server(void);

void Lawliet_APP_Start(void);
void Lawliet_APP_Stop(void);


#ifdef __cplusplus
}
#endif

#endif /* _APP_COMMON_H_ */
