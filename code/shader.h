#ifndef SHADER_H
#define SHADER_H

#include <stdint.h>

struct Shader 
{
    unsigned int ID;
    uint32_t view_location;
    uint32_t proj_location;
    uint32_t world_location;
    uint32_t texture_location;
    uint32_t has_color;
    uint32_t immune_location;
    uint32_t color_location;
};

void shader_load(Shader* shader, const char* vertex_path, const char* fragment_path);
void shader_use(uint32_t id);

#endif

