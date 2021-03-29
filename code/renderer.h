#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include <string>
#include <vector>
#include "win32_utility.h"
#include "shader.h"
#include "math.h"

struct Shaders
{
    Shader main_shader;
};

struct Camera
{
    Vec3 up;
    Vec3 dir;
    Vec3 pos;
};

void setup_renderer();
void add_texture(std::string id, const char* texture_filepath, bool is_tilesheet);
Texture* get_texture(std::string id);
std::vector<uint32_t> load_tilesheet(std::string id, int num_cols, int num_rows, int size);
void draw_rect_color(int x, int y, int width, int height, Vec3 color);
void draw_rect_texture(int x, int y, int width, int height, std::string id);
void draw_tilesheet_tile(int x, int y, int width, int height, uint32_t tex_id);
Camera* get_camera();

#endif
