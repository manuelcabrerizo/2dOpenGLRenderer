#ifndef PLAYSTATE
#define PLAYSTATE

#include "./win32_app.h"

enum Play_States
{
    GAMEPLAYSTATE,
    TALKINGSTATE,
};

enum Player_State
{
    ALIVE,
    DEAD
};

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
    Player_State player_state;
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

    Vec2 finish_zone;
    int finish_tilemap_x;
    int finish_tilemap_y;
    
    Vec2 death_position;
    int death_tilemap_x;
    int death_tilemap_y;

    Vec2 killing_machine;
    int kill_tilemap_x;
    int kill_tilemap_y;

    Vec2 start_kill;
    int start_tilemap_x;
    int start_tilemap_y;

    bool follow_player;
    Vec2 princess;
    int princess_tilemap_x;
    int princess_tilemap_y;

};

void play_state_start(Game_State* state);
void play_state_update(float delta_time, Game_State* state);
void play_state_render();
void play_state_restart();

#endif
