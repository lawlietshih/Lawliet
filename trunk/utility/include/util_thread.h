#ifndef _UTIL_THREAD_H_
#define _UTIL_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h> /* Portable for 64bit */
#include <stdbool.h>
#include <pthread.h>
#include "../../include/prj_errno.h"

#define PTHREAD_ATTR_INIT(a) 			 pthread_attr_init(a)
#define PTHREAD_ATTR_SETDETACHSTATE(a,s) pthread_attr_setdetachstate(a,s)
#define PTHREAD_ATTR_DESTROY(a)			 pthread_attr_destroy(a)
#define PTHREAD_MUTEX_TRYLOCK(m)		 pthread_mutex_trylock(m)
#define PTHREAD_MUTEX_LOCK(m)			 pthread_mutex_lock(m)
#define PTHREAD_MUTEX_UNLOCK(m)			 pthread_mutex_unlock(m)
#define PTHREAD_MUTEX_INIT(m,a)			 pthread_mutex_init(m,a)
#define PTHREAD_MUTEX_DESTROY(m)		 pthread_mutex_destroy(m)
#define PTHREAD_CREATE(t,att,c,arg)		 pthread_create(t,att,c,arg)
#define PTHREAD_JOIN(t,r)				 pthread_join(t,r)
#define PTHREAD_COND_INIT(c,a)			 pthread_cond_init(c,a)
#define	PTHREAD_COND_WAIT(c,m)			 pthread_cond_wait(c,m)
#define	PTHREAD_COND_TIMEWAIT(c,m,t)	 pthread_cond_timedwait(c,m,t)
#define PTHREAD_COND_BROADCAST(c)		 pthread_cond_broadcast(c)
#define PTHREAD_COND_SIGNAL(c)			 pthread_cond_signal(c)
#define PTHREAD_COND_DESTROY(c)			 pthread_cond_destroy(c)
#define PTHREAD_EXIT(n)					 pthread_exit(n)

/* Thread state */
#define TH_SLEEP 0
#define TH_RUNNING 1

typedef struct _thread_t {
	bool exit_thread;
	bool state_to_set;
	bool state;
	char *name;
	pthread_t tid;
	pthread_mutex_t lock;
	pthread_cond_t cond_lock;
	void (*func)(void *);
	void *private_data;
} thread_t;


PRJResult thread_init(thread_t *thread, void *func, void *private_data);

PRJResult thread_destroy(thread_t *thread);

void thread_run(thread_t *thread);

void thread_stop(thread_t *thread);

void thread_wakeup(thread_t *thread);

void thread_wait(thread_t *thread);

void thread_timedwait(thread_t *thread, struct timespec *ts);

void thread_sleep(thread_t *thread);

void thread_setname(thread_t *thread, char *name);

#ifdef __cplusplus
}
#endif

#endif /* __UTIL_THREAD_H_ */

