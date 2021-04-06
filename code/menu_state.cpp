#include "./menu_state.h"
#include "./renderer.h"

#include "./play_state.h"

global_variable Menu main_menu;

void menu_state_start(Game_State* state)
{
    add_texture("button-0", "./data/play_button.bmp", false);
    add_texture("button-1", "./data/play_button_selected.bmp", false);
    add_texture("button-exit-0", "./data/exit_button.bmp", false);
    add_texture("button-exit-1", "./data/exit_button_selected.bmp", false);
    main_menu.option_selected = 0;
}

void menu_state_update(float delta_time, Game_State* state)
{
    Input* input = get_input();
    if(key_down(VK_RETURN, input))
    {
        if(main_menu.option_selected == 1)
        {
            play_state_restart();
            main_menu.option_selected = 0;
            *state = PLAY_STATE;
        }
        
        if(main_menu.option_selected == 2)
        {
            bool* app_running = get_app_running();
            *app_running = false;
        }

    }
    static bool w_was_press = false;
    if(key_down('W', input) && w_was_press == false)
    {
        w_was_press = true;
        if(main_menu.option_selected > 0)
            main_menu.option_selected--;
    }
    if(keys_up('W', input))
    {
        w_was_press = false;
    }

    static bool s_was_press = false;
    if(key_down('S', input) && s_was_press == false)
    {
        s_was_press = true;
        if(main_menu.option_selected < 2)
            main_menu.option_selected++;
    }
    if(keys_up('S', input))
    {
        s_was_press = false;
    }
}

void menu_state_render()
{
    if(main_menu.option_selected == 1)
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 80*4, 64* 4, 32*4, "button-1");
    else
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 80*4, 64* 4, 32*4, "button-0");

    if(main_menu.option_selected == 2)
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 32*4, 64*4, 32*4, "button-exit-1");
    else
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 32*4, 64*4, 32*4, "button-exit-0");
}
