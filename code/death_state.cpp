#include "./death_state.h"
#include "./renderer.h"

#include "./play_state.h"

global_variable Death_State death_menu;

void death_state_start(Game_State* state)
{
    add_texture("menu-button-0", "./data/menu_button.bmp", false);
    add_texture("menu-button-1", "./data/menu_button_selected.bmp", false);
    add_texture("death_back", "./data/death_background.bmp", false);
    death_menu.option_selected = 0;
}

void death_state_update(float delta_time, Game_State* state)
{
    Input* input = get_input();
    if(key_down(VK_RETURN, input))
    {
        if(death_menu.option_selected == 1)
        {
            play_state_restart();
            set_immune_shader_filter(0);
            death_menu.option_selected = 0;
            *state = PLAY_STATE;
        }
        
        if(death_menu.option_selected == 2)
        {
            set_immune_shader_filter(0);
            death_menu.option_selected = 0;
            *state = MENU_STATE;
        }

    }
    static bool w_was_press = false;
    if(key_down('W', input) && w_was_press == false)
    {
        w_was_press = true;
        if(death_menu.option_selected > 0)
            death_menu.option_selected--;
    }
    if(keys_up('W', input))
    {
        w_was_press = false;
    }

    static bool s_was_press = false;
    if(key_down('S', input) && s_was_press == false)
    {
        s_was_press = true;
        if(death_menu.option_selected < 2)
            death_menu.option_selected++;
    }
    if(keys_up('S', input))
    {
        s_was_press = false;
    }
}

void death_state_render()
{
    if(death_menu.option_selected == 1)
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 80*4, 64* 4, 32*4, "button-1");
    else
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 80*4, 64* 4, 32*4, "button-0");
    if(death_menu.option_selected == 2)
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 32*4, 64*4, 32*4, "menu-button-1");
    else
        draw_rect_texture((WNDWIDTH / 2) - 32*4, 32*4, 64*4, 32*4, "menu-button-0");

    draw_rect_texture(0, 0, 320 * 4, 180 * 4, "death_back");

}
