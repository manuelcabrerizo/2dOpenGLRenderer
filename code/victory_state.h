#ifndef VICTORY_H
#define VICTORY_H

#include "./win32_app.h"

struct Victory
{
    int option_selected;
};

void victory_state_start(Game_State* state);
void victory_state_update(float delta_time, Game_State* state);
void victory_state_render();

#endif
