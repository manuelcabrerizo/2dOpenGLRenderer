#ifndef WIN32APP_H
#define WIN32APP_H

#include <stdint.h>
#include <windows.h>
#include "win32_input.h"
#include "math.h"
#include <vector>


enum Game_State
{
    INIT_STATE,
    MENU_STATE,
    PLAY_STATE,
    DEATH_STATE
};

struct Animation
{
    int row = 4;
    int col = 0;
    int num_frames = 6;
    float speed = 20.0f;
};

void win32_start();
void win32_update(float delta_time);
void win32_render();

#endif
