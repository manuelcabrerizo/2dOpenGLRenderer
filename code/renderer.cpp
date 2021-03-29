#include <windows.h>
#include <glad/glad.h>
#include <map>
#include "renderer.h"

global_variable Shaders shaders;
global_variable Camera camera;
global_variable Quad rect_texture;
global_variable std::map<std::string, Texture> textures;

void setup_renderer()
{
    shader_load(&shaders.main_shader, "./code/main_shader.vert", "./code/main_shader.frag");
    
    camera.up =  {0.0f,  1.0f,  0.0f};
    camera.dir = {0.0f,  0.0f,  1.0f};
    camera.pos = {0.0f,  0.0f, -1.0f};
    Matrix view = get_view_matrix(camera.pos, camera.dir, camera.up);
    Matrix proj = get_projection_orthogonal_matrix(WNDWIDTH, WNDHEIGHT, 0.0f, 100.0f);
    shader_use(shaders.main_shader.ID);
    shaders.main_shader.view_location = glGetUniformLocation(shaders.main_shader.ID, "view");
    glUniformMatrix4fv(shaders.main_shader.view_location, 1, GL_FALSE, view.m[0]);
    shaders.main_shader.proj_location = glGetUniformLocation(shaders.main_shader.ID, "proj");
    glUniformMatrix4fv(shaders.main_shader.proj_location, 1, GL_FALSE, proj.m[0]); 
    shaders.main_shader.texture_location = glGetUniformLocation(shaders.main_shader.ID, "texture1");
    glUniform1i(shaders.main_shader.texture_location, 0);
    shaders.main_shader.world_location = glGetUniformLocation(shaders.main_shader.ID, "model");
    shaders.main_shader.has_color = glGetUniformLocation(shaders.main_shader.ID, "has_color");
    shaders.main_shader.color_location = glGetUniformLocation(shaders.main_shader.ID, "color");

    rect_texture = setup_quad();
    glBindVertexArray(rect_texture.vao);
    glActiveTexture(GL_TEXTURE0);
}

Camera* get_camera()
{
    return &camera;
}

void add_texture(std::string id, const char* texture_filepath, bool is_tilesheet)
{ 
    textures.emplace(id, load_bmp(texture_filepath, is_tilesheet));  
}

Texture* get_texture(std::string id)
{
    return &textures[id];
}

std::vector<uint32_t> load_tilesheet(std::string id, int num_cols, int num_rows, int size)
{
    std::vector<uint32_t> textures_ids;
    Texture* texture = get_texture(id);

     for(int y = 0; y < num_rows; y++)
     {
        for(int x = 0; x < num_cols; x++)
        {
            
            uint32_t* new_texture = (uint32_t*)malloc((size * size) * sizeof(uint32_t));
            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < size; j++)
                {
                    new_texture[(i * size) + j] = texture->pixels[((i + (y * size) ) * (size * num_cols)) + (j + (x * size))];
                }
            }
            uint32_t texture_id;
            glGenTextures(1, &texture_id);
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            if(new_texture != NULL)
            { 
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size,
                                            0, GL_BGRA, GL_UNSIGNED_BYTE, new_texture);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            textures_ids.push_back(texture_id);
            free(new_texture);
        }
     }
     return textures_ids;
}

void draw_rect_color(int x, int y, int width, int height, Vec3 color)
{
    glUniform1i(shaders.main_shader.has_color, 1);
    glUniform3f(shaders.main_shader.color_location, color.x, color.y, color.z);
    Matrix model = get_scale_matrix({(float)width, (float)height, 1.0f}) * get_translation_matrix({(float)x + (width/2.0f), (float)y + (height/2.0f), 0.0f});
    glUniformMatrix4fv(shaders.main_shader.world_location, 1, GL_FALSE, model.m[0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void draw_rect_texture(int x, int y, int width, int height, std::string id)
{
    glUniform1i(shaders.main_shader.has_color, 0);
    Texture* texture = get_texture(id); 
    glBindTexture(GL_TEXTURE_2D, texture->id);
    Matrix model = get_scale_matrix({(float)width, (float)height, 1.0f}) * get_translation_matrix({(float)x + (width/2.0f), (float)y + (height/2.0f), 0.0f});
    glUniformMatrix4fv(shaders.main_shader.world_location, 1, GL_FALSE, model.m[0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void draw_tilesheet_tile(int x, int y, int width, int height, uint32_t tex_id)
{
    glUniform1i(shaders.main_shader.has_color, 0);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    Matrix model = get_scale_matrix({(float)width, (float)height, 1.0f}) * get_translation_matrix({(float)x + (width/2.0f), (float)y + (height/2.0f), 0.0f});
    glUniformMatrix4fv(shaders.main_shader.world_location, 1, GL_FALSE, model.m[0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
