#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "./win32_app.h"

struct Menu
{
    int option_selected;
};

void menu_state_start(Game_State* state);
void menu_state_update(float delta_time, Game_State* state);
void menu_state_render();

#endif
