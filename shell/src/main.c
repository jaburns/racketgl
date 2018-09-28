#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glew.h>

#include "media.h"
#include "thread.h"
#include "render.h"

#define DLL_EXPORT __declspec(dllexport)

typedef struct StartupArgs
{
    const char *title;
    int width;
    int height;
}
StartupArgs;

typedef struct ShellState
{
    ThreadHandle thread;
    bool running;
    MutexHandle sim_state_mutex;
    SimState sim_state;
}
ShellState;

static ShellState s_shell;

static void main_loop(void *vargs)
{
    StartupArgs args = *(StartupArgs*)vargs;
    free(vargs);

    media_open(args.title, args.width, args.height);

    do
    {
        mutex_acquire(s_shell.sim_state_mutex);
        render_sim_state(&s_shell.sim_state);
        mutex_release(s_shell.sim_state_mutex);
    }
    while (s_shell.running && media_flip_frame_poll_events());

    s_shell.running = false;
    media_close();
}

DLL_EXPORT void shell_open(const char *title, int width, int height)
{
    if (s_shell.running) return;

    s_shell.running = true;

    StartupArgs *args = malloc(sizeof(StartupArgs));
    args->title = title;
    args->width = width;
    args->height = height;

    s_shell.sim_state_mutex = mutex_create();
    s_shell.sim_state = default_sim_state();
    s_shell.thread = thread_start(main_loop, args);
}

DLL_EXPORT bool shell_is_open()
{
    return s_shell.running;
}

DLL_EXPORT void shell_update(const SimState *state)
{
    mutex_acquire(s_shell.sim_state_mutex);
    s_shell.sim_state = *state;
    mutex_release(s_shell.sim_state_mutex);
}

DLL_EXPORT InputState *shell_borrow_input_state(void)
{
    return read_input_state();
}

DLL_EXPORT void shell_release_input_state(InputState *state)
{
    free_input_state(state);
}

DLL_EXPORT void shell_close(void)
{
    if (!s_shell.running) return;

    s_shell.running = false;

    thread_join(s_shell.thread);
    mutex_destroy(s_shell.sim_state_mutex);

    s_shell.sim_state_mutex = NULL;
    s_shell.thread = NULL;
}
