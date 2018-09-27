#include "render.h"

#include <GL/glew.h>

SimState default_sim_state(void)
{
    SimState result;
    result.red = 0.2f;
    result.green = 0.2f;
    result.blue = 0.2f;
    return result;
}

void render_sim_state(const SimState *state)
{
    glClearColor(state->red, state->green, state->blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}