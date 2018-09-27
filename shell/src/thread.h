#pragma once

typedef void *MutexHandle;
typedef void *ThreadHandle;
typedef void(*ThreadProc)(void*);

extern ThreadHandle thread_start(ThreadProc proc, void *args);
extern void thread_join(ThreadHandle);

extern MutexHandle mutex_create(void);
extern void mutex_acquire(MutexHandle);
extern void mutex_release(MutexHandle);
extern void mutex_destroy(MutexHandle);