#include "thread.h"

#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>

typedef struct ThreadArg
{
    ThreadProc proc;
    void *args;
}
ThreadArg;

static DWORD WINAPI thread_body(LPVOID lpParam)
{
    ThreadArg thread_arg = *(ThreadArg*)lpParam;
    free(lpParam);

    thread_arg.proc(thread_arg.args);
}

ThreadHandle thread_start(ThreadProc proc, void *args)
{
    ThreadArg *thread_arg = malloc(sizeof(ThreadArg));
    thread_arg->proc = proc;
    thread_arg->args = args;
    return CreateThread(NULL, 0, thread_body, thread_arg, 0, NULL);
}

void thread_join(ThreadHandle handle)
{
    WaitForSingleObject(handle, INFINITE);
}

MutexHandle mutex_create(void)
{
    return CreateMutex(NULL, FALSE, NULL);
}

void mutex_acquire(MutexHandle mutex)
{
    WaitForSingleObject(mutex, INFINITE);
}

void mutex_release(MutexHandle mutex)
{
    ReleaseMutex(mutex);
}

void mutex_destroy(MutexHandle mutex)
{
    CloseHandle(mutex);
}
