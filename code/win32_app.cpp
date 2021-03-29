#include "./win32_app.h"
#include "./renderer.h"

Entity_Manager Game::manager;
std::vector<uint32_t> mago_aminations;
std::vector<uint32_t> tile_map_textures;

uint32_t tile_map00[144] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0,
    1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
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



Vec2 player_pos = {2.0f * 64, 2.0f * 64};
int player_speed = 200;
Animation animation;
Tile_Map map;
World world;

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
    world.world.x     = 0.0f;
    world.world.y     = 0.0f;
    world.pos.x       = 2.0f * world.tile_size.x;  
    world.pos.y       = 2.0f * world.tile_size.y;
    world.tile.x      = world.pos.x / world.tile_size.x;
    world.tile.y      = world.pos.y / world.tile_size.y;

}

uint32_t* get_tiles(uint32_t x, uint32_t y)
{
    uint32_t* tiles = 0;
    if((x >= 0) && (x < 2) &&
       (y >= 0) && (y < 2))
    {
        tiles = map.tiles[(y * 2) + x];
    }
    return tiles;
}

bool check_tile_empty(uint32_t tilemap_x, uint32_t tilemap_y, uint32_t tile_x, uint32_t tile_y)
{
    bool empty = false;
    if((tile_x >= 0) && (tile_x < 16) &&
       (tile_y >= 0) && (tile_y < 9))
    {
        uint32_t* tile_map = get_tiles(tilemap_x, tilemap_y);
        uint32_t tilemap_value = tile_map[(tile_y * 16) + tile_x]; 
        empty = (tilemap_value == 0);
    }
    return empty;
}

bool check_world_tile_empty_test(uint32_t test_tilemap_x, uint32_t test_tilemap_y ,float test_x, float test_y)
{   
    bool empty = false; 
    int32_t test_tile_x = (int32_t)floorf(test_x / world.tile_size.x);
    int32_t test_tile_y = (int32_t)floorf(test_y / world.tile_size.y);

    if(test_tile_x < 0)
    {
        test_tile_x = 16 + test_tile_x;
        test_tilemap_x--;
    }
    if(test_tile_x >= 16)
    {
        test_tile_x = test_tile_x - 16;
        test_tilemap_x++;
    }
    if(test_tile_y < 0)
    {
        test_tile_y = 9 + test_tile_y; 
        test_tilemap_y++;
    }
    if(test_tile_y >= 9)
    {
        test_tile_y = test_tile_y - 9;
        test_tilemap_y--;
    }

    empty = check_tile_empty(test_tilemap_x, test_tilemap_y, test_tile_x, test_tile_y);
    return empty;
}


bool check_world_tile_empty(float x, float y)
{
    world.tile.x = floorf(x / world.tile_size.x);
    world.tile.y = floorf(y / world.tile_size.y);    
    
    if(world.tile.x < 0)
    {
        world.tile.x = 15;
        world.world.x--;
        player_pos.x += 15 * 64;
        OutputDebugString("paseee x perro!!!!\n");
        return false;
    }
    if(world.tile.x >= 16)
    {
        world.tile.x = 0;
        world.world.x++;
        player_pos.x -= 15 * 64;
        OutputDebugString("paseee x perro!!!!\n");
        return false;
    }
    if(world.tile.y < 0)
    {
        world.tile.y = 8;
        world.world.y++;
        player_pos.y += 8 * 64;
        OutputDebugString("paseee y perro!!!!\n");
        return false;
    }
    if(world.tile.y >= 9)
    {
        world.tile.y = 0;
        world.world.y--;
        player_pos.y -= 8 * 64;
        return false;
    }

    if(map.tiles[(uint32_t)((world.world.y * 2) + world.world.x)][((uint32_t)world.tile.y * 16) + (uint32_t)world.tile.x] == 0)
    {
        return  true;
    }  
    return false;
}


void win32_update(float delta_time)
{
    animation.num_frames = 1;

    Vec2 player_new_position = player_pos;

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
 
    if(check_world_tile_empty_test(0, 0, player_new_position.x + 0.4f*64.0f, player_new_position.y) &&
       check_world_tile_empty_test(0, 0, player_new_position.x + 0.6f*64.0f, player_new_position.y) &&
       check_world_tile_empty_test(0, 0, player_new_position.x + 0.4f*64.0f, player_new_position.y + 0.6*64.0f) &&
       check_world_tile_empty_test(0, 0, player_new_position.x + 0.6f*64.0f, player_new_position.y + 0.6*64.0f))
    {
        player_pos = player_new_position;
    }

    static float time = 0;
    time += delta_time;
    animation.col = (int)((int)(time * animation.speed) % animation.num_frames);
}

void win32_render()
{
    draw_tilesheet_tile(player_pos.x, player_pos.y, 64, 64, mago_aminations[(animation.row * 6) + animation.col]); 
    int tilemap_count_x = 16;
    int tilemap_count_y = 9;
    int tile_size = 64;
    int tile_texture = 32;
    for(int y = 0; y < 9; y++)
    {
        for(int x = 0; x < 16; x++)
        {
            if(map.tiles[(uint32_t)((world.world.y * 2) + world.world.x)][(y*tilemap_count_x)+x] == 0)
                tile_texture = 35;
            else
                tile_texture = 18;
            draw_tilesheet_tile(x * tile_size, y * tile_size, tile_size, tile_size, tile_map_textures[tile_texture]);
        }
    }
}
