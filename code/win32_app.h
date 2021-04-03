#ifndef WIN32APP_H
#define WIN32APP_H

#include <stdint.h>
#include <windows.h>
#include "ecs.h"
#include "win32_input.h"

#include <vector>

struct Game
{
    static Entity_Manager manager;
};

struct Animation
{
    int row = 4;
    int col = 0;
    int num_frames = 6;
    float speed = 20.0f;
};

struct Fireball
{
    Vec2 position;
    Vec2 direction;
    float speed;
    Animation animation;
};

struct Enemy 
{
    float shoot_speed;
    int tile_map_x;
    int tile_map_y;
    Vec2 position;
    Fireball fireball;
};

struct Tile_Map
{
    uint32_t tile_count_x = 16;
    uint32_t tile_count_y = 9;
    uint32_t* tiles[4];
};


struct World
{
    Tile_Map map;
    Vec2 tile_map;
    Vec2 tile;
    Vec2 pos;
    Vec2 dir;
    Vec2 tile_size;
    uint32_t tile_map_count_x = 2;
    uint32_t tile_map_count_y = 2;
    Enemy* enemies;
    int num_enemy;
};

void win32_start();
void win32_update(float delta_time);
void win32_render();

#endif
