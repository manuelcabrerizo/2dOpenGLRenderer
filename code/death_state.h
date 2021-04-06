#ifndef DEATHSTATE_H
#define DEATHSTATE_H

#include "./win32_app.h"

struct Death_State
{
   int option_selected; 
};

void death_state_start(Game_State* state);
void death_state_update(float delta_time, Game_State* state);
void death_state_render();

#endif
