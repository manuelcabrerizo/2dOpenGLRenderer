#include "./win32_app.h"
#include "./renderer.h"

Entity_Manager Game::manager;
std::vector<uint32_t> mago_aminations;
std::vector<uint32_t> tile_map_textures;
std::vector<uint32_t> fireball_textures;

uint32_t tile_map00[144] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
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
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
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
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
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
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
};

global_variable int player_speed = 200;
global_variable float player_size = 64.0f;
global_variable Animation animation;

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

void win32_start()
{
    add_texture("enemy", "./data/enemy.bmp", false);
    add_texture("fireball", "./data/fireball.bmp", true);
    fireball_textures = load_tilesheet("fireball", 6, 4, 8); 
    add_texture("mago", "./data/mago.bmp", true);
    mago_aminations = load_tilesheet("mago", 6, 5, 16);
    add_texture("map", "./data/tilesheet.bmp", true);
    tile_map_textures = load_tilesheet("map", 6, 6, 16);

    world.map.tiles[0] = tile_map00;
    world.map.tiles[1] = tile_map01;
    world.map.tiles[2] = tile_map10;
    world.map.tiles[3] = tile_map11;

    world.tile_size = {80.0f, 80.0f};
    world.tile_map  = {0.0f, 0.0f};
    world.pos       = {2.0f * world.tile_size.x, 2.0f * world.tile_size.y};  
    world.dir       = {1.0f, 0.0f};
    world.tile      = {world.pos.x / world.tile_size.x, world.pos.y / world.tile_size.y};

    Animation spell_animation = {3, 0, 6, 10.0f}; 
    for(int i = 0; i < world.num_fireballs; i++)
    {
        world.fireballs[i].position = world.pos;
        world.fireballs[i].direction = world.dir;
        world.fireballs[i].speed = 300;
        world.fireballs[i].animation = spell_animation;
        world.fireballs[i].should_render = false;
    }
    initialize_enemies(&world);
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

void process_enemy_fireball(Enemy* enemy, Vec2 player_pos, float time, float delta_time)
{
    enemy->fireball.animation.col = (int)((int)(time * enemy->fireball.animation.speed) % enemy->fireball.animation.num_frames);    
    float fireball_distane = absf(vec2_length(enemy->fireball.position - enemy->position)); 
    if(fireball_distane == 0)
    {
        enemy->fireball.direction = normaliza_vec2(player_pos - enemy->position); 
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
}

void process_player_spell(Fireball* fireball, Vec2 player_pos, float time, float delta_time)
{
    fireball->animation.col = (int)((int)(time * fireball->animation.speed) % fireball->animation.num_frames);
    if(absf(vec2_length(player_pos - fireball->position)) > 300)
    {
        fireball->should_render = false; 
    }
    //if(fireball->should_render == true)
    {
        fireball->position = fireball->position + (fireball->direction * fireball->speed) * delta_time;
    }
}

void shoot_spell(Fireball* fireball, Vec2 player_pos)
{
    if(fireball->should_render == false)
        fireball->position = player_pos;
    fireball->should_render = true;
}

void win32_update(float delta_time)
{
    animation.num_frames = 1;
    Vec2 player_new_position = world.pos;

    Input* input = get_input();
    bool up    = key_down('W'     , input);
    bool down  = key_down('S'     , input);
    bool left  = key_down('A'     , input);
    bool right = key_down('D'     , input);
    bool space = key_down(VK_SPACE, input);

    if(space)
    {
        shoot_spell(&world.fireballs[0], world.pos);
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
    }
    if(world.tile.x >= world.map.tile_count_x)
    {
        world.tile_map.x += 1.0f;
        world.pos.x -= world.map.tile_count_x * world.tile_size.x;
    }
    if(world.tile.y < 0)
    {
        world.tile_map.y += 1.0f;
        world.pos.y += world.map.tile_count_y * world.tile_size.y; 
    }
    if(world.tile.y >= world.map.tile_count_y)
    {
        world.tile_map.y -= 1.0f;
        world.pos.y -= world.map.tile_count_y * world.tile_size.y;
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
        {     
            process_enemy_fireball(enemy, world.pos, time, delta_time);
        }
    }

    for(int i = 0; i < world.num_fireballs; i++)
    {
        process_player_spell(&world.fireballs[i], world.pos, time, delta_time);
    }
}

void win32_render()
{
    for(int i = 0; i < world.num_enemy; i++)
    {
        if((uint32_t)world.tile_map.x == world.enemies[i].tile_map_x &&
           (uint32_t)world.tile_map.y == world.enemies[i].tile_map_y)
        {
            draw_tilesheet_tile(world.enemies[i].fireball.position.x,
                                world.enemies[i].fireball.position.y,
                                48, 48,
                                fireball_textures[(world.enemies[i].fireball.animation.row * 6) + world.enemies[i].fireball.animation.col]);
            draw_rect_texture(world.enemies[i].position.x, world.enemies[i].position.y, 64, 64, "enemy");
        }
    }

    for(int i = 0; i < world.num_fireballs; i++)
    {
        //if(world.fireballs[i].should_render == true)
        {
            draw_tilesheet_tile(world.fireballs[i].position.x, 
                            world.fireballs[i].position.y,
                            48, 48, 
                            fireball_textures[(world.fireballs[i].animation.row * 6) + world.fireballs[i].animation.col]);
        }
    }

    draw_tilesheet_tile(world.pos.x, world.pos.y, (int)player_size, (int)player_size,
                        mago_aminations[(animation.row * 6) + animation.col]);

    int tile_texture = 35;
    for(int y = 0; y < world.map.tile_count_y; y++)
    {
        for(int x = 0; x < world.map.tile_count_x; x++)
        {
            uint32_t* tiles = get_tiles(world, (uint32_t)world.tile_map.x, (uint32_t)world.tile_map.y);
            if(tiles)
            {
                if(tiles[(y*world.map.tile_count_x)+x] != 1)
                {
                    tile_texture = 35;
                }
                else if(tiles[(y*world.map.tile_count_x)+x] == 1)
                {
                    tile_texture = 18;
                }
                draw_tilesheet_tile(x * world.tile_size.x, y * world.tile_size.y, world.tile_size.x, world.tile_size.y, tile_map_textures[tile_texture]);
            }
        }
    }

}
