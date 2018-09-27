#pragma once

typedef struct SimState
{
    float red;
    float green;
    float blue;
}
SimState;

extern SimState default_sim_state(void);
extern void render_sim_state(const SimState *state);