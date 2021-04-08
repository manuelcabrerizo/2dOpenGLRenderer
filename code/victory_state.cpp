#include "./victory_state.h"
#include "./renderer.h"

#include "./play_state.h"

global_variable Victory victory_menu;

void victory_state_start(Game_State* state)
{
    add_texture("victory_back", "./data/victory_background.bmp", false);
    victory_menu.option_selected = 0;
}

void victory_state_update(float delta_time, Game_State* state)
{
    Input* input = get_input();
    if(key_down(VK_RETURN, input))
    {
        if(victory_menu.option_selected == 1)
        {
            play_state_restart();
            set_immune_shader_filter(0);
            victory_menu.option_selected = 0;
            *state = PLAY_STATE;
        }
        
        if(victory_menu.option_selected == 2)
        {
            set_immune_shader_filter(0);
            victory_menu.option_selected = 0;
            *state = MENU_STATE;
        }

    }
    static bool w_was_press = false;
    if(key_down('W', input) && w_was_press == false)
    {
        w_was_press = true;
        if(victory_menu.option_selected > 0)
            victory_menu.option_selected--;
    }
    if(keys_up('W', input))
    {
        w_was_press = false;
    }

    static bool s_was_press = false;
    if(key_down('S', input) && s_was_press == false)
    {
        s_was_press = true;
        if(victory_menu.option_selected < 2)
            victory_menu.option_selected++;
    }
    if(keys_up('S', input))
    {
        s_was_press = false;
    }
}

void victory_state_render()
{
    if(victory_menu.option_selected == 1)
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 80*4, 64* 4, 32*4, "button-1");
    else
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 80*4, 64* 4, 32*4, "button-0");
    if(victory_menu.option_selected == 2)
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 32*4, 64*4, 32*4, "menu-button-1");
    else
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 32*4, 64*4, 32*4, "menu-button-0");

    draw_rect_texture(0, 0, 320 * 4, 180 * 4, "victory_back");
}
