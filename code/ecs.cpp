#include "win32_app.h"

Entity* add_entity(const char* name)
{
    Entity* new_entity = (Entity*)malloc(sizeof(Entity));
    new_entity->name = name;
    Game::manager.entities.push_back(new_entity);
    return new_entity;
}
void add_component(Entity* entity, int pos_x, int pos_y, int vel_x, int vel_y, int width, int height, int scale)
{
    Transform_Component new_component;
    new_component.owner = entity;
    new_component.position = {(float)pos_x, (float)pos_y};
    new_component.velocity = {(float)vel_x, (float)vel_y};
    new_component.width = width;
    new_component.height = height;
    new_component.scale = scale;
    Game::manager.transform_components.push_back(new_component); 
}


