#include "play_state.h"
#include "./renderer.h"

std::vector<uint32_t> mago_aminations;
std::vector<uint32_t> tile_map_textures;
std::vector<uint32_t> fireball_textures;
std::vector<uint32_t> spell_textures;
std::vector<uint32_t> mago_dead_animations;
Play_States play_state;

uint32_t tile_map00_textures[144] = {
    21, 21, 21, 21, 21, 21, 21, 24, 26, 21, 21, 21, 21, 21, 21, 21,
    21, 18, 19, 19, 19, 20, 21, 24, 26, 21, 18, 19, 19, 19, 20, 21,
    21, 24, 25, 25, 25, 25, 25, 25, 26, 21, 24, 25, 25, 25, 26, 21,
    21, 30, 31, 31, 31, 32, 21, 24, 26, 21, 24, 25, 25, 25, 26, 21,
    21, 21, 21, 21, 21, 21, 21, 24, 26, 21, 24, 25, 25, 25, 25, 25,
    21, 18, 19, 19, 19, 19, 19, 34, 26, 21, 24, 25, 25, 25, 26, 21,
    21, 24, 25, 25, 25, 25, 25, 25, 26, 21, 24, 25, 25, 25, 26, 21,
    21, 30, 31, 31, 31, 31, 31, 31, 32, 21, 30, 31, 31, 31, 32, 21,
    21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21
};

uint32_t tile_map01_textures[144] = {
    21, 21, 21, 21, 21, 21, 21, 24, 26, 21, 21, 21, 21, 21, 21, 21,
    21, 18, 19, 19, 19, 19, 19, 25, 25, 19, 19, 19, 19, 19, 20, 21,
    21, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 21,
    21, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 21,
    25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 21,
    21, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 21,
    21, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 21,
    21, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 21,
    21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21
};

uint32_t tile_map10_textures[144] = {
    3,  3,  3,  3,  3,  3,  3, 3, 3,  3,  3,  3,  3,  3,  3, 3,
    3,  0,  1,  1,  1,  1,  1, 1, 1,  1,  1,  1,  1,  1,  2, 3,
    3,  6,  7,  7,  7,  7,  7, 7, 7,  7,  7,  7,  7,  7,  8, 3,
    3,  6,  7,  7,  7,  7,  7, 7, 7,  7,  7,  7,  7,  7,  8, 3,
    3,  6,  7,  7,  7,  7,  7, 7, 7,  7,  7,  7,  7,  7,  7, 7,
    3,  6,  7,  7,  7,  7,  7, 7, 7,  7,  7,  7,  7,  7,  8, 3,
    3,  6,  7,  7,  7,  7,  7, 7, 7,  7,  7,  7,  7,  7,  8, 3,
    3, 12, 13, 13, 13, 13, 13, 7, 7, 13, 13, 13, 13, 13, 14, 3,
    3,  3,  3,  3,  3,  3,  3, 7, 7,  3,  3,  3,  3,  3,  3, 3
};

uint32_t tile_map11_textures[144] = {
    3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3, 3,
    3,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2, 3,
    3,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 3,
    3,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 3,
    7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 3,
    3,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 3,
    3,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 3,
    3, 12, 13, 13, 13, 13, 13,  7,  7, 13, 13, 13, 13, 13, 14, 3,
    3,  3,  3,  3,  3,  3,  3,  7,  7,  3,  3,  3,  3,  3,  3, 3
};


uint32_t tile_map00[144] = {
    1, 1, 1, 1, 1, 1, 1, 0, 3, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 5, 0, 0, 4, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

uint32_t tile_map01[144] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

uint32_t tile_map10[144] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1
};

uint32_t tile_map11[144] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1
};

global_variable int player_speed = 200;
global_variable float player_size = 64.0f;
global_variable Animation animation;
global_variable bool show_collitions = false;
global_variable World world;

void initialize_enemies(World* world)
{
    int num_enemy = 0;
    for(int i = 0; i < world->tile_map_count_x * world->tile_map_count_y; i++)
    {
        uint32_t* tiles = world->map.tiles[i];
        for(int y = 0; y < world->map.tile_count_y; y++)
        {
            for(int x = 0; x < world->map.tile_count_x; x++)
            {
                if(tiles[(y * world->map.tile_count_x) + x] == 2)
                {
                    num_enemy++;
                }
            }
        }
    }
    world->enemies = (Enemy*)malloc(num_enemy * sizeof(Enemy));
    world->num_enemy = num_enemy;
    int enemy_index = 0;
    for(int tile_map_y = 0; tile_map_y < world->tile_map_count_y; tile_map_y++)
    {
        for(int tile_map_x = 0; tile_map_x < world->tile_map_count_x; tile_map_x++)
        {

            uint32_t* tiles = world->map.tiles[(tile_map_y * world->tile_map_count_x) + tile_map_x];
            for(int y = 0; y < world->map.tile_count_y; y++)
            {
                for(int x = 0; x < world->map.tile_count_x; x++)
                {
                    if(tiles[(y * world->map.tile_count_x) + x] == 2)
                    {
                        Enemy* enemy = &world->enemies[enemy_index];
                        enemy->tile_map_x = tile_map_x;
                        enemy->tile_map_y = tile_map_y;
                        enemy->position = { (float)x * world->tile_size.x, (float)y * world->tile_size.y };
                        enemy->life                   = 3;
                        enemy->text_id                = "enemy";
                        enemy->timer                  = 0.0f;
                        enemy->start_timer            = false;
                        enemy->fireball.animation.row = 3;
                        enemy->fireball.animation.col = 0;
                        enemy->fireball.animation.num_frames = 6;
                        enemy->fireball.animation.speed = 10.0f;
                        enemy->fireball.position      = enemy->position;  
                        enemy->fireball.direction     = {1.0f, 1.0f};
                        enemy->fireball.speed         = 300.0f;
                        enemy_index++;
                    }
                }
            }

        }
    }
}

void play_state_start(Game_State* state)
{
    play_state = GAMEPLAYSTATE;
    add_texture("casa", "./data/casa.bmp", false);
    add_texture("princess", "./data/princess.bmp", false);
    add_texture("die-here", "./data/die-here.bmp", false);
    add_texture("pinches", "./data/pinches.bmp", false);
    add_texture("death", "./data/deaht.bmp", false);
    add_texture("death-dialog", "./data/death_dialog.bmp", false);
    add_texture("life", "./data/life.bmp", false);
    add_texture("enemy", "./data/enemy.bmp", false);
    add_texture("enemy-damage", "./data/enemy_damage.bmp", false);
    add_texture("collition", "./data/collition.bmp", false);
    add_texture("spell", "./data/spell.bmp", true);
    spell_textures = load_tilesheet("spell", 6, 4, 8);
    add_texture("fireball", "./data/fireball.bmp", true);
    fireball_textures = load_tilesheet("fireball", 6, 4, 8); 
    add_texture("mago", "./data/mago.bmp", true);
    mago_aminations = load_tilesheet("mago", 6, 5, 16);
    add_texture("map", "./data/new_tilesheet.bmp", true);
    tile_map_textures = load_tilesheet("map", 6, 6, 16);
    add_texture("mago-dead", "./data/mago-dead.bmp", true);
    mago_dead_animations = load_tilesheet("mago-dead", 6, 5, 16);

    world.map.tiles[0] = tile_map00;
    world.map.tiles[1] = tile_map01;
    world.map.tiles[2] = tile_map10;
    world.map.tiles[3] = tile_map11;

    world.map.tiles_textures[0] = tile_map00_textures;
    world.map.tiles_textures[1] = tile_map01_textures;
    world.map.tiles_textures[2] = tile_map10_textures;
    world.map.tiles_textures[3] = tile_map11_textures;

    world.player_state = ALIVE;
    world.tile_size = {80.0f, 80.0f};
    world.tile_map  = {0.0f, 0.0f};
    world.pos       = {2.0f * world.tile_size.x, 2.0f * world.tile_size.y};  
    world.dir       = {1.0f, 0.0f};
    world.tile      = {world.pos.x / world.tile_size.x, world.pos.y / world.tile_size.y};
    world.life      = 5;
    world.immune    = false;
    Animation spell_animation = {3, 0, 6, 10.0f}; 
    world.fireball.position = world.pos;
    world.fireball.direction = world.dir;
    world.fireball.speed = 500;
    world.fireball.animation = spell_animation;
    world.fireball.should_render = false;
    world.death_tilemap_x = 0;
    world.death_tilemap_y = 0;

    world.finish_zone.x = 11 * 80;
    world.finish_zone.y = 2 * 80;
    world.finish_tilemap_x = 0;
    world.finish_tilemap_y = 0;

    world.kill_tilemap_x = 0;
    world.kill_tilemap_y = 0;
    world.killing_machine.x = 8 * 80;
    world.killing_machine.y = 7 * 80;

    world.start_tilemap_x = 0;
    world.start_tilemap_y = 0;
    world.start_kill.x = 5 * 80;
    world.start_kill.y = 7 * 80;

    world.follow_player = false;
    world.princess_tilemap_x = 1;
    world.princess_tilemap_y = 0;
    world.princess.x = 7 * 80;
    world.princess.y = 4 * 80;

    initialize_enemies(&world);
}

void play_state_restart()
{
    world.finish_zone.x = 11 * 80;
    world.finish_zone.y = 2 * 80;
    world.finish_tilemap_x = 0;
    world.finish_tilemap_y = 0;

    world.follow_player = false;
    world.princess_tilemap_x = 1;
    world.princess_tilemap_y = 0;
    world.princess.x = 7 * 80;
    world.princess.y = 4 * 80;

    world.player_state = ALIVE;
    world.kill_tilemap_x = 0;
    world.kill_tilemap_y = 0;
    world.killing_machine.x = 8 * 80;
    world.killing_machine.y = 7 * 80;

    world.start_tilemap_x = 0;
    world.start_tilemap_y = 0;
    world.start_kill.x = 5 * 80;
    world.start_kill.y = 7 * 80;

    world.life = 5;
    set_immune_shader_filter(0);
    world.tile_map  = {0.0f, 0.0f};
    world.pos = {2.0f * world.tile_size.x, 2.0f * world.tile_size.y}; 
    for(int i = 0; i < world.num_enemy; i++)
    {
        Enemy* enemy = &world.enemies[i];
        enemy->timer = 0.0f;
        enemy->start_timer = false;
        enemy->life = 3;
        enemy->text_id = "enemy";
        enemy->fireball.should_render = false;
        enemy->fireball.position = enemy->position;
        enemy->fireball.direction     = {1.0f, 1.0f};
    }
}

bool aabb_colition_check(float x0, float y0, float width0, float height0,
                         float x1, float y1, float width1, float height1)
{
    if(x0 < x1 + width1  &&
       x0 + width0 > x1  && 
       y0 < y1 + height1 &&
       y0 + height0 > y1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

uint32_t* get_tiles_texture(World, uint32_t x, uint32_t y)
{
    uint32_t* tiles = 0;
    if((x >= 0) && (x < world.tile_map_count_x) &&
       (y >= 0) && (y < world.tile_map_count_y))
    {
        tiles = world.map.tiles_textures[(y * world.tile_map_count_x) + x];
    }
    return tiles;

}

uint32_t* get_tiles(World world, uint32_t x, uint32_t y)
{
    uint32_t* tiles = 0;
    if((x >= 0) && (x < world.tile_map_count_x) &&
       (y >= 0) && (y < world.tile_map_count_y))
    {
        tiles = world.map.tiles[(y * world.tile_map_count_x) + x];
    }
    return tiles;
}

bool check_tile_empty(World world, uint32_t tilemap_x, uint32_t tilemap_y, uint32_t tile_x, uint32_t tile_y)
{
    bool empty = false;
    if((tile_x >= 0) && (tile_x < world.map.tile_count_x) &&
       (tile_y >= 0) && (tile_y < world.map.tile_count_y))
    {
        uint32_t* current_tile_map = get_tiles(world, tilemap_x, tilemap_y);
        if(current_tile_map)
        {
            uint32_t tilemap_value = current_tile_map[(tile_y * world.map.tile_count_x) + tile_x]; 
            empty = (tilemap_value != 1);
        }
    }
    return empty;
}

bool check_world_tile_empty_test(World world, float test_x, float test_y)
{   
    bool empty = false; 
    int32_t test_tile_x = (int32_t)floorf(test_x / world.tile_size.x);
    int32_t test_tile_y = (int32_t)floorf(test_y / world.tile_size.y);
    uint32_t test_tilemap_x = (uint32_t)world.tile_map.x;
    uint32_t test_tilemap_y = (uint32_t)world.tile_map.y;

    if(test_tile_x < 0)
    {
        test_tile_x = world.map.tile_count_x + test_tile_x;
        test_tilemap_x--;
    }
    if(test_tile_x >= world.map.tile_count_x)
    {
        test_tile_x = test_tile_x - world.map.tile_count_x;
        test_tilemap_x++;
    }
    if(test_tile_y < 0)
    {
        test_tile_y = world.map.tile_count_y + test_tile_y; 
        test_tilemap_y++;
    }
    if(test_tile_y >= world.map.tile_count_y)
    {
        test_tile_y = test_tile_y - world.map.tile_count_y;
        test_tilemap_y--;
    }

    empty = check_tile_empty(world, test_tilemap_x, test_tilemap_y, test_tile_x, test_tile_y);
    return empty;
}

void process_enemy_fireball(Enemy* enemy, World* world, float time, float delta_time)
{
    enemy->fireball.animation.col = (int)((int)(time * enemy->fireball.animation.speed) % enemy->fireball.animation.num_frames);    
    float fireball_distane = absf(vec2_length(enemy->fireball.position - enemy->position)); 
    if(fireball_distane == 0)
    {
        enemy->fireball.direction = normaliza_vec2(world->pos - enemy->position); 
    }
    if(fireball_distane > 1280)
    {
        enemy->fireball.position = enemy->position;
    }
    else
    { 
        enemy->fireball.position  = enemy->fireball.position + (enemy->fireball.direction * enemy->fireball.speed) * delta_time;
    }
    if(absf(enemy->fireball.direction.x) > absf(enemy->fireball.direction.y))
    {
        if(enemy->fireball.direction.x > 0)
        {
            enemy->fireball.animation.row = 1;
        }
        else
        {
            enemy->fireball.animation.row = 3;
        }
    }
    else
    {
        if(enemy->fireball.direction.y > 0)
        {
            enemy->fireball.animation.row = 2;
        }
        else
        {
            enemy->fireball.animation.row = 0;
        }   
    }
    if(show_collitions)
    {
        draw_rect_texture(world->pos.x + 16, world->pos.y, 32, 48, "collition");
        draw_rect_texture(enemy->fireball.position.x + 8, enemy->fireball.position.y + 8, 32, 32, "collition");
    }
    if(aabb_colition_check(world->pos.x + 16, world->pos.y, 32, 48,
                           enemy->fireball.position.x + 8, enemy->fireball.position.y + 8, 32, 32) &&
                           world->immune == false)
    {
        if(world->life > 0)
            world->life--;
        set_immune_shader_filter(1);
        world->immune = true;
    }
    
     
    if(show_collitions)
    {
        draw_rect_texture(enemy->position.x, enemy->position.y, 48, 48, "collition");
    }
    if(world->fireball.should_render)
    { 
        if(show_collitions)
        {
            draw_rect_texture(world->fireball.position.x + 8, world->fireball.position.y + 8, 32, 32, "collition");
        }
        if(aabb_colition_check(world->fireball.position.x + 8, world->fireball.position.y + 8, 32, 32,
                               enemy->position.x, enemy->position.y, 48, 48))
        {
            enemy->life--;
            enemy->text_id = "enemy-damage";
            enemy->start_timer = true;
            world->fireball.should_render = false;
        }
    }

    if(enemy->start_timer)
    {
        enemy->timer += delta_time;
        if(enemy->timer > 1.0f)
        {
            enemy->timer = 0.0f;
            enemy->text_id = "enemy";
        }
    }
}

void process_player_spell(Fireball* fireball, Vec2 player_pos, float time, float delta_time)
{
    fireball->animation.col = (int)((int)(time * fireball->animation.speed) % fireball->animation.num_frames);
    if(absf(vec2_length(fireball->start_position - fireball->position)) > 300)
    {
        fireball->should_render = false; 
    }
    fireball->position = fireball->position + (fireball->direction * fireball->speed) * delta_time;    
}

void shoot_spell(Fireball* fireball, Vec2 player_pos, Vec2 player_dir)
{
    if(absf(vec2_length(fireball->start_position - fireball->position)) > 300)
    {
        fireball->start_position = player_pos;
        fireball->direction = player_dir;
        fireball->position = player_pos;
        if(animation.row == 0)
        {
            fireball->animation.row = 2;
        }
        if(animation.row == 1)
        {
            fireball->animation.row = 0;
        }
        if(animation.row == 2)
        {
            fireball->animation.row = 1;
        }
        if(animation.row == 3)
        {
            fireball->animation.row = 3;
        }
        fireball->should_render = true;
    }
}

void play_state_update(float delta_time, Game_State* state)
{
    if(play_state == GAMEPLAYSTATE)
    {
        animation.num_frames = 1;
        Vec2 player_new_position = world.pos;

        Input* input = get_input();
        bool up    = key_down('W',      input);
        bool down  = key_down('S',      input);
        bool left  = key_down('A',      input);
        bool right = key_down('D',      input);
        bool space = key_down(VK_SPACE, input);
        bool colitions = key_down('P', input);
    
        static bool colitions_was_press = false; 
        if(colitions && show_collitions == false && colitions_was_press == false)
        {
            show_collitions = true;
            colitions_was_press = true;
        }
        else if(colitions && show_collitions == true && colitions_was_press == false)
        {
            show_collitions = false;
            colitions_was_press = true;
        }
        if(keys_up('P', input))
        {
            colitions_was_press = false;
        }

        if(up && !left && !right && !down)
        {
            Vec2 new_dir = vec2_rotate(world.dir, to_radiant(90));
            player_new_position = player_new_position + (new_dir * player_speed) * delta_time;
            animation.row = 0;
            animation.num_frames = 6;
        }
        else if(down && !left && !right && !up)
        {
            Vec2 new_dir = vec2_rotate(world.dir, to_radiant(270));
            player_new_position = player_new_position + (new_dir * player_speed) * delta_time;
            animation.row = 1;
            animation.num_frames = 6;
        }
        else if(left && !up && !down && !right)
        {
            Vec2 new_dir = vec2_rotate(world.dir, to_radiant(180));
            player_new_position = player_new_position + (new_dir * player_speed) * delta_time;
            animation.row = 3;
            animation.num_frames = 6;
        }
        else if(right && !up && !down && !left)
        {
            Vec2 new_dir = vec2_rotate(world.dir, to_radiant(0));
            player_new_position = player_new_position + (new_dir * player_speed) * delta_time;
            animation.row = 2;
            animation.num_frames = 6;
        }
        else if(right && up && !left && !down)
        {
            Vec2 new_dir = vec2_rotate(world.dir, to_radiant(45));
            player_new_position = player_new_position + (new_dir * player_speed) * delta_time;
            animation.row = 2;
            animation.num_frames = 6;
        }
        else if(left && up && !right && !down)
        {
            Vec2 new_dir = vec2_rotate(world.dir, to_radiant(135));
            player_new_position = player_new_position + (new_dir * player_speed) * delta_time;
            animation.row = 3;
            animation.num_frames = 6; 
        }
        else if(right && down && !left && !up)
        {
            Vec2 new_dir = vec2_rotate(world.dir, to_radiant(315));
            player_new_position = player_new_position + (new_dir * player_speed) * delta_time;
            animation.row = 2;
            animation.num_frames = 6; 
        }
        else if(left && down && !right && !up)
        {
            Vec2 new_dir = vec2_rotate(world.dir, to_radiant(225));
            player_new_position = player_new_position + (new_dir * player_speed) * delta_time;
            animation.row = 3;
            animation.num_frames = 6;
        } 

        Vec2 spell_dir;
        if(animation.row == 0)
        {
            spell_dir = {0.0f, 1.0f};
        }
        if(animation.row == 1)
        {
            spell_dir = {0.0f, -1.0f};
        }
        if(animation.row == 2)
        {
            spell_dir = {1.0f, 0.0f};
        }
        if(animation.row == 3)
        {
            spell_dir = {-1.0f, 0.0f};
        }
        if(space)
        {
            shoot_spell(&world.fireball, world.pos, spell_dir);
        }

        if(check_world_tile_empty_test(world, player_new_position.x + 0.4f*player_size, player_new_position.y) &&
           check_world_tile_empty_test(world, player_new_position.x + 0.6f*player_size, player_new_position.y) &&
           check_world_tile_empty_test(world, player_new_position.x + 0.4f*player_size, player_new_position.y + 0.6*player_size) &&
           check_world_tile_empty_test(world, player_new_position.x + 0.6f*player_size, player_new_position.y + 0.6*player_size))
        {
            world.pos = player_new_position;
        }

        world.tile.x = (int32_t)floorf((world.pos.x + (player_size/2.0f)) / world.tile_size.x);
        world.tile.y = (int32_t)floorf((world.pos.y + (player_size/2.0f)) / world.tile_size.y);

        if(world.tile.x < 0)
        {
            world.tile_map.x -= 1.0f;
            world.pos.x += world.map.tile_count_x * world.tile_size.x;
            if(world.follow_player)
                world.princess.x += world.map.tile_count_x * world.tile_size.x;
        }
        if(world.tile.x >= world.map.tile_count_x)
        {
            world.tile_map.x += 1.0f;
            world.pos.x -= world.map.tile_count_x * world.tile_size.x;
            if(world.follow_player)
                world.princess.x -= world.map.tile_count_x * world.tile_size.x;

        }
        if(world.tile.y < 0)
        {
            world.tile_map.y += 1.0f;
            world.pos.y += world.map.tile_count_y * world.tile_size.y;
            if(world.follow_player)
                world.princess.y += world.map.tile_count_y * world.tile_size.y;
        }
        if(world.tile.y >= world.map.tile_count_y)
        {
            world.tile_map.y -= 1.0f;
            world.pos.y -= world.map.tile_count_y * world.tile_size.y;
            if(world.follow_player)
                world.princess.y -= world.map.tile_count_y * world.tile_size.y;
        }

        // handle animations
        static float time = 0;
        time += delta_time;
        animation.col = (int)((int)(time * animation.speed) % animation.num_frames);
    
        // handle enemies
        for(int i = 0; i < world.num_enemy; i++)
        {
            Enemy* enemy = &world.enemies[i];
            if(enemy->tile_map_x == world.tile_map.x && enemy->tile_map_y == world.tile_map.y)
            {       if(enemy->life > 0)   
                    process_enemy_fireball(enemy, &world, time, delta_time);
            }
        }
        static float immune_timer = 0.0f;
        if(world.immune == true)
        {
            immune_timer += delta_time;
            if(immune_timer > 2.0f)
            {
                set_immune_shader_filter(0);
                world.immune = false;
                immune_timer = 0.0f;
            }
        }
        process_player_spell(&world.fireball, world.pos, time, delta_time);

        if(world.life == 0)
        {
            *state = DEATH_STATE;
        }


        if(world.kill_tilemap_x == world.tile_map.x &&
           world.kill_tilemap_y == world.tile_map.y && 
           world.start_tilemap_x == world.tile_map.x &&
           world.start_tilemap_y == world.tile_map.y)
        {
            if(aabb_colition_check(world.pos.x, world.pos.y, 64, 64,
                                   world.start_kill.x, world.start_kill.y, 64, 64) &&
                !aabb_colition_check(world.killing_machine.x, world.killing_machine.y, 64, 64,
                                   world.start_kill.x, world.start_kill.y, 2, 64))
            {
                Vec2 kill_machine_direction = {-1.0f, 0.0f};
                world.killing_machine = world.killing_machine + ((kill_machine_direction * 300) * delta_time);
            }

            if(aabb_colition_check(world.pos.x, world.pos.y, 64, 64,
                                   world.killing_machine.x, world.killing_machine.y, 64, 64) && 
               aabb_colition_check(world.pos.x, world.pos.y, 64, 64,
                                   world.start_kill.x, world.start_kill.y, 64, 64))
            {
                world.player_state = DEAD;
            }
        }

        if(world.princess_tilemap_x == world.tile_map.x &&
           world.princess_tilemap_y == world.tile_map.y)
        {
            if(aabb_colition_check(world.pos.x, world.pos.y, 64, 64,
                                   world.princess.x, world.princess.y, 64, 64) && world.follow_player == false)
            {
                world.follow_player = true; 
            }
        }

        if(world.follow_player)
        {
            world.princess_tilemap_x = world.tile_map.x;
            world.princess_tilemap_y = world.tile_map.y;
            if(vec2_length(world.pos - world.princess) <= 256)
            {
                Vec2 princes_dir = normaliza_vec2(world.pos - world.princess);
                world.princess = world.princess + ((princes_dir * 150) * delta_time);
            } 
        }

        if(world.princess_tilemap_x == world.finish_tilemap_x &&
           world.princess_tilemap_y == world.finish_tilemap_y)
        {
            if(aabb_colition_check(world.finish_zone.x, world.finish_zone.y, 48 * 4, 32 * 4,
                                   world.princess.x, world.princess.y, 64, 64))
            {
                *state = MENU_STATE; 
            }
        }

    
        if(world.death_tilemap_x == world.tile_map.x && world.death_tilemap_y == world.tile_map.y && world.player_state == ALIVE)
        {
            //draw_rect_texture(world.death_position.x - 80, world.death_position.y, 160, 40, "collition");
            if(aabb_colition_check(world.pos.x, world.pos.y, 64, 64,
                                   world.death_position.x - 80, world.death_position.y, 160, 40))
            {
                play_state = TALKINGSTATE;      
            }
        }
    }
    else if(play_state == TALKINGSTATE)
    {
        Input* input = get_input();
        if(key_down(VK_RETURN, input))
        {
            world.pos.y += 5.0f;
            play_state = GAMEPLAYSTATE;
        } 
    }
}

void play_state_render()
{
    if(play_state == TALKINGSTATE)
    {   
        draw_rect_texture(0, 0, (256+ 64) * 4, 64 * 4, "death-dialog");
    }
    
    if(play_state == GAMEPLAYSTATE || play_state == TALKINGSTATE)
    {
        for(int life_index = 0; life_index < world.life; life_index++)
        {
            draw_rect_texture(0 + (life_index * 64), WNDHEIGHT - 104, 64, 64, "life");
        }

        for(int i = 0; i < world.num_enemy; i++)
        {
            if((uint32_t)world.tile_map.x == world.enemies[i].tile_map_x &&
               (uint32_t)world.tile_map.y == world.enemies[i].tile_map_y)
            {
                if(world.enemies[i].life > 0)
                {
                    draw_tilesheet_tile(world.enemies[i].fireball.position.x,
                                        world.enemies[i].fireball.position.y,
                                        48, 48,
                                        fireball_textures[(world.enemies[i].fireball.animation.row * 6) + world.enemies[i].fireball.animation.col]);
                    draw_rect_texture(world.enemies[i].position.x, world.enemies[i].position.y, 64, 64, world.enemies[i].text_id);
                }
            }
        }

        if(world.fireball.should_render == true)
        {
            draw_tilesheet_tile(world.fireball.position.x, 
                                world.fireball.position.y,
                                48, 48, 
                                spell_textures[(world.fireball.animation.row * 6) + world.fireball.animation.col]);
        }
    
        if(world.player_state == ALIVE)
        {
            draw_tilesheet_tile(world.pos.x, world.pos.y, (int)player_size, (int)player_size,
                                mago_aminations[(animation.row * 6) + animation.col]); 
        }
        else
        {
            draw_tilesheet_tile(world.pos.x, world.pos.y, (int)player_size, (int)player_size,
                                mago_dead_animations[(animation.row * 6) + animation.col]);
        }

        if(world.kill_tilemap_x == world.tile_map.x &&
           world.kill_tilemap_y == world.tile_map.y && 
           world.start_tilemap_x == world.tile_map.x &&
           world.start_tilemap_y == world.tile_map.y)
        {
            draw_rect_texture(world.killing_machine.x, world.killing_machine.y, 64, 64, "pinches"); 
            draw_rect_texture(world.start_kill.x, world.start_kill.y, 64, 128, "die-here");
        }
        if(world.princess_tilemap_x == world.tile_map.x &&
           world.princess_tilemap_y == world.tile_map.y)
        {
            draw_rect_texture(world.princess.x, world.princess.y, 64, 64, "princess");
        }
        if(world.finish_tilemap_x == world.tile_map.x &&
           world.finish_tilemap_y == world.tile_map.y)
        {
            draw_rect_texture(world.finish_zone.x, world.finish_zone.y, 48 * 4, 32 * 4, "casa");
        }

        int tile_texture = 35;
        for(int y = 0; y < world.map.tile_count_y; y++)
        {
            for(int x = 0; x < world.map.tile_count_x; x++)
            {
                uint32_t* tiles = get_tiles_texture(world, (uint32_t)world.tile_map.x, (uint32_t)world.tile_map.y);
                uint32_t* tiles_value = get_tiles(world, (uint32_t)world.tile_map.x, (uint32_t)world.tile_map.y);

                if(tiles_value)
                {
                    if(tiles_value[(y*world.map.tile_count_x)+x] == 3)
                    {
                        world.death_position.x = x * world.tile_size.x;
                        world.death_position.y = y * world.tile_size.y;
                        draw_rect_texture(world.death_position.x, world.death_position.y, 64, 64, "death");
                    }
                }
                if(tiles)
                {
                    tile_texture = tiles[(y*world.map.tile_count_x)+x];
                    draw_tilesheet_tile(x * world.tile_size.x, y * world.tile_size.y, world.tile_size.x, world.tile_size.y, tile_map_textures[tile_texture]);
                }
            }
        }
    }
}
