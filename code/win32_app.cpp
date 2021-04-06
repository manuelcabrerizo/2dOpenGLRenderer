#include "./play_state.h"
#include "./menu_state.h"
#include "./death_state.h"

Game_State main_state;

void win32_start()
{
    main_state = MENU_STATE;
    menu_state_start(&main_state); 
    play_state_start(&main_state);   
    death_state_start(&main_state);
}

void win32_update(float delta_time)
{
    if(main_state == MENU_STATE)
    {
        menu_state_update(delta_time, &main_state); 
    }
    else if(main_state == PLAY_STATE)
    {
        play_state_update(delta_time, &main_state);
    }
    else if(main_state == DEATH_STATE)
    {
        death_state_update(delta_time, &main_state);
    }
}

void win32_render()
{
    if(main_state == MENU_STATE)
    {
        menu_state_render();
    }
    else if(main_state == PLAY_STATE)
    {
        play_state_render();
    }
    else if(main_state == DEATH_STATE)
    {
        death_state_render();
    }
}


