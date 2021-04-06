#ifndef PLAYSTATE
#define PLAYSTATE

#include "./win32_app.h"

struct Fireball
{
    Vec2 start_position;
    Vec2 position;
    Vec2 direction;
    float speed;
    Animation animation;
    bool should_render = true;
};

struct Enemy 
{
    float shoot_speed;
    int tile_map_x;
    int tile_map_y;
    Vec2 position;
    Fireball fireball;
    int life;
    const char* text_id;
    float timer;
    bool start_timer;
};

struct Tile_Map
{
    uint32_t tile_count_x = 16;
    uint32_t tile_count_y = 9;
    uint32_t* tiles[4];
    uint32_t* tiles_textures[4];
};


struct World
{
    Tile_Map map;
    Vec2 tile_map;
    Vec2 tile;
    Vec2 pos;
    Vec2 dir;
    int life;
    bool immune;
    Fireball fireball;
    Vec2 tile_size;
    uint32_t tile_map_count_x = 2;
    uint32_t tile_map_count_y = 2;
    Enemy* enemies;
    int num_enemy;
};

void play_state_start(Game_State* state);
void play_state_update(float delta_time, Game_State* state);
void play_state_render();
void play_state_restart();

#endif
