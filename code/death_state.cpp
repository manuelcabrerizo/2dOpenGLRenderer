#include "./death_state.h"
#include "./renderer.h"

void death_state_start(Game_State* state)
{
    add_texture("menu-button-0", "./data/menu_button.bmp", false);
    add_texture("menu-button-0", "./data/menu_button_selected.bmp", false);
}

void death_state_update(float delta_time, Game_State* state)
{

}

void death_state_render()
{
    draw_rect_texture((WNDWIDTH / 2) - 32*4, 80*4, 64* 4, 32*4, "button-0");
    draw_rect_texture((WNDWIDTH / 2) - 32*4, 32*4, 64*4, 32*4, "menu-button-0");
}
