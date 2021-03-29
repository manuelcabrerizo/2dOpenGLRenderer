#ifndef ECS_H
#define ECS_H

#include <stdint.h>
#include <vector>
#include "math.h"


struct Entity
{
    const char* name;
};

struct Transform_Component
{
    Entity* owner;
    Vec2 position;
    Vec2 velocity;
    int width;
    int height;
    int scale;
};

struct Sprite_Component
{

};

struct Entity_Manager
{
    std::vector<Entity*> entities;
    std::vector<Transform_Component> transform_components;
};

Entity* add_entity(const char* name);
void add_component(Entity* entity, int pos_x, int pos_y, int vel_x, int vel_y, int width, int height, int scale);

#endif
