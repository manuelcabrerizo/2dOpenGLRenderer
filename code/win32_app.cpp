#include "./win32_app.h"
#include "./renderer.h"

Entity_Manager Game::manager;
std::vector<uint32_t> mago_aminations;
std::vector<uint32_t> tile_map_textures;

uint32_t tile_map00[144] = {
    1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0,
    1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

uint32_t tile_map01[144] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

uint32_t tile_map10[144] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
};

uint32_t tile_map11[144] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
};

global_variable int player_speed = 200;
global_variable float player_size = 64.0f;
global_variable Animation animation;
global_variable Tile_Map map;
global_variable World world;

void win32_start()
{ 
    add_texture("mago", "./data/mago.bmp", true);
    mago_aminations = load_tilesheet("mago", 6, 5, 16);
    add_texture("map", "./data/tilesheet.bmp", true);
    tile_map_textures = load_tilesheet("map", 6, 6, 16);

    map.tiles[0] = tile_map00;
    map.tiles[1] = tile_map01;
    map.tiles[2] = tile_map10;
    map.tiles[3] = tile_map11;

    world.tile_size.x = 64.0f;
    world.tile_size.y = 64.0f;
    world.tile_map.x     = 0.0f;
    world.tile_map.y     = 0.0f;
    world.pos.x       = 2.0f * world.tile_size.x;  
    world.pos.y       = 2.0f * world.tile_size.y;
    world.tile.x      = world.pos.x / world.tile_size.x;
    world.tile.y      = world.pos.y / world.tile_size.y;
}

uint32_t* get_tiles(World world, Tile_Map* tile_map, uint32_t x, uint32_t y)
{
    uint32_t* tiles = 0;
    if((x >= 0) && (x < world.tile_map_count_x) &&
       (y >= 0) && (y < world.tile_map_count_y))
    {
        tiles = tile_map->tiles[(y * world.tile_map_count_x) + x];
    }
    return tiles;
}

bool check_tile_empty(World world, Tile_Map* tile_map, uint32_t tilemap_x, uint32_t tilemap_y, uint32_t tile_x, uint32_t tile_y)
{
    bool empty = false;
    if((tile_x >= 0) && (tile_x < tile_map->tile_count_x) &&
       (tile_y >= 0) && (tile_y < tile_map->tile_count_y))
    {
        uint32_t* current_tile_map = get_tiles(world, tile_map, tilemap_x, tilemap_y);
        if(current_tile_map)
        {
            uint32_t tilemap_value = current_tile_map[(tile_y * tile_map->tile_count_x) + tile_x]; 
            empty = (tilemap_value == 0);
        }
    }
    return empty;
}

bool check_world_tile_empty_test(World world, Tile_Map* tile_map, float test_x, float test_y)
{   
    bool empty = false; 
    int32_t test_tile_x = (int32_t)floorf(test_x / world.tile_size.x);
    int32_t test_tile_y = (int32_t)floorf(test_y / world.tile_size.y);
    uint32_t test_tilemap_x = (uint32_t)world.tile_map.x;
    uint32_t test_tilemap_y = (uint32_t)world.tile_map.y;

    if(test_tile_x < 0)
    {
        test_tile_x = tile_map->tile_count_x + test_tile_x;
        test_tilemap_x--;
    }
    if(test_tile_x >= tile_map->tile_count_x)
    {
        test_tile_x = test_tile_x - tile_map->tile_count_x;
        test_tilemap_x++;
    }
    if(test_tile_y < 0)
    {
        test_tile_y = tile_map->tile_count_y + test_tile_y; 
        test_tilemap_y++;
    }
    if(test_tile_y >= tile_map->tile_count_y)
    {
        test_tile_y = test_tile_y - tile_map->tile_count_y;
        test_tilemap_y--;
    }

    empty = check_tile_empty(world, tile_map, test_tilemap_x, test_tilemap_y, test_tile_x, test_tile_y);
    return empty;
}

void win32_update(float delta_time)
{

    world.tile.x = (int32_t)floorf((world.pos.x + (player_size/2.0f)) / world.tile_size.x);
    world.tile.y = (int32_t)floorf((world.pos.y + (player_size/2.0f)) / world.tile_size.y);

    if(world.tile.x < 0)
    {
        world.tile_map.x -= 1.0f;
        world.pos.x += map.tile_count_x * player_size; 
    }
    if(world.tile.x >= map.tile_count_x)
    {
        world.tile_map.x += 1.0f;
        world.pos.x -= map.tile_count_x * player_size;
    }
    if(world.tile.y < 0)
    {
        world.tile_map.y += 1.0f;
        world.pos.y += map.tile_count_y * player_size; 
    }
    if(world.tile.y >= map.tile_count_y)
    {
        world.tile_map.y -= 1.0f;
        world.pos.y -= map.tile_count_y * player_size;
    }

    animation.num_frames = 1;

    Vec2 player_new_position = world.pos;

    Input* input = get_input();
    if(key_down('W', input) == true)
    {
        player_new_position.y += player_speed * delta_time;
        animation.row = 0;
        animation.num_frames = 6;
    }
    if(key_down('S', input) == true)
    {
        player_new_position.y -= player_speed * delta_time;
        animation.row = 1;
        animation.num_frames = 6;
    }
    if(key_down('A', input) == true)
    {
        player_new_position.x -= player_speed * delta_time;
        animation.row = 3;
        animation.num_frames = 6;
    }
    if(key_down('D', input) == true)
    {
        player_new_position.x += player_speed * delta_time;
        animation.row = 2;
        animation.num_frames = 6;
    }
 
    if(check_world_tile_empty_test(world, &map, player_new_position.x + 0.4f*player_size, player_new_position.y) &&
       check_world_tile_empty_test(world, &map, player_new_position.x + 0.6f*player_size, player_new_position.y) &&
       check_world_tile_empty_test(world, &map, player_new_position.x + 0.4f*player_size, player_new_position.y + 0.6*player_size) &&
       check_world_tile_empty_test(world, &map, player_new_position.x + 0.6f*player_size, player_new_position.y + 0.6*player_size))
    {
        world.pos = player_new_position;
    }

    static float time = 0;
    time += delta_time;
    animation.col = (int)((int)(time * animation.speed) % animation.num_frames);
}

void win32_render()
{
    draw_tilesheet_tile(world.pos.x, world.pos.y, (int)player_size, (int)player_size,
                        mago_aminations[(animation.row * 6) + animation.col]); 
    int tile_texture = 35;
    for(int y = 0; y < map.tile_count_y; y++)
    {
        for(int x = 0; x < map.tile_count_x; x++)
        {
            uint32_t* tiles = get_tiles(world, &map, (uint32_t)world.tile_map.x, (uint32_t)world.tile_map.y);
            if(tiles)
            {
                if(tiles[(y*map.tile_count_x)+x] == 0)
                {
                    tile_texture = 35;
                }
                else
                {
                    tile_texture = 18;
                }
                draw_tilesheet_tile(x * world.tile_size.x, y * world.tile_size.y, world.tile_size.x, world.tile_size.y, tile_map_textures[tile_texture]);
            }
        }
    }

