#include "./init_state.h"
#include "./renderer.h"

void init_state_start(Game_State* state)
{
    add_texture("tutorial", "./data/tutorial.bmp", false);
}
void init_state_update(float delta_time, Game_State* state)
{
    static float timer = 0;
    timer += delta_time;
    if(timer > 10.0f)
    {
        *state = MENU_STATE;
    }
}
void init_state_render()
{
    draw_rect_texture(0 , 0, 320 * 4, 180 * 4, "tutorial");
}
