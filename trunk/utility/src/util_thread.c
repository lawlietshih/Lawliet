#include <string.h>

#include "../../include/prj_errno.h"
#include "../../include/prj_types.h"
#include "../include/util_thread.h"

PRJResult thread_init(thread_t *thread, void *func, void *private_data)
{
	if (!thread)
		return PRJ_ERROR;

	bzero(thread, sizeof(thread_t));

	PTHREAD_MUTEX_INIT(&thread->lock, NULL);
	PTHREAD_COND_INIT(&thread->cond_lock, NULL);

	thread->func = func;
	thread->private_data = private_data;

	thread->exit_thread = false;
	thread->state_to_set = TH_SLEEP;
	return PRJ_OK;
}

PRJResult thread_destroy(thread_t *thread)
{
	SAFE_FREE(thread->name);
	PTHREAD_MUTEX_DESTROY(&thread->lock);
	PTHREAD_COND_DESTROY(&thread->cond_lock);

	return PRJ_OK;
}

void thread_run(thread_t *thread)
{
	PTHREAD_CREATE(&thread->tid, NULL, (void *)thread->func, (void *)thread);
}

void thread_stop(thread_t *thread)
{
	thread->exit_thread = true;
	PTHREAD_JOIN(thread->tid, NULL);
}

void thread_wakeup(thread_t *thread)
{
	thread->state_to_set = TH_RUNNING;
	PTHREAD_COND_SIGNAL(&thread->cond_lock);
}

void thread_sleep(thread_t *thread)
{
	thread->state_to_set = TH_SLEEP;
}

void thread_wait(thread_t *thread)
{
	PTHREAD_MUTEX_LOCK(&thread->lock);
	PTHREAD_COND_WAIT(&thread->cond_lock, &thread->lock);
	PTHREAD_MUTEX_UNLOCK(&thread->lock);
}

void thread_timedwait(thread_t *thread, struct timespec *ts)
{
	PTHREAD_MUTEX_LOCK(&thread->lock);
	PTHREAD_COND_TIMEWAIT(&thread->cond_lock, &thread->lock, ts);
	PTHREAD_MUTEX_UNLOCK(&thread->lock);
}

void thread_setname(thread_t *thread, char *name)
{
	thread->name = strdup(name);
}
