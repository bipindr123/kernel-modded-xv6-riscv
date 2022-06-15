#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/thread.h"
#include "kernel/spinlock.h"

void lock_init(lock_t *lock)
{
	*lock = 0;
}
void lock_acquire(lock_t *lock)
{
	while(__sync_lock_test_and_set(lock, 1) != 0);
	__sync_synchronize();
}
void lock_release(lock_t *lock)
{
	__sync_synchronize();
	__sync_lock_release(lock,0);
}

int thread_create(void *(*start_routine)(void*), void *arg) {
	void* stack = (void*)malloc(4096 * sizeof(void));
	int tid  = clone(stack,(int)(4096 * sizeof(void)));
	if(tid == 0) 
	{
		(*start_routine) (arg);
		exit(0);
	}
	return 0;
}