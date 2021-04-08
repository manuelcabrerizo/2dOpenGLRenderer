#ifndef INITSTATE_H
#define INITSTATE_H

#include "./win32_app.h"

void init_state_start(Game_State* state);
void init_state_update(float delta_time, Game_State* state);
void init_state_render();

#endif
