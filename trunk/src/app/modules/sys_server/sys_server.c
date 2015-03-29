#include "../../../../include/prj_types.h"
#include "../../include/app_common.h"

int syssrv_run = 1;

void Init_System_Server(void)
{
	PTHREAD       pid;
	PTHREADATTR   attr;

	PTHREAD_ATTR_INIT(&attr);
	PTHREAD_ATTR_SETDETACHSTATE(&attr,PTHREAD_CREATE_DETACHED);
	PTHREAD_CREATE(&pid, &attr, SysSrvThread, NULL);
	PTHREAD_ATTR_DESTROY(&attr);
}

void Destroy_System_Server(void)
{
	syssrv_run = 0;
}

void *SysSrvThread(void *p)
{
	while(syssrv_run){
		LDBG("sys_server live... !\n");
		sleep(3);
	}

	LDBG("System Server 881... !\n");
	
	return NULL;
}


