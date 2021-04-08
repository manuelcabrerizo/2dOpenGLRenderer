#ifndef WIN32UTILITY_H
#define WIN32UTILITY_H

#include <windows.h>
#include <objbase.h>
#include <glad/glad.h>
#include <GL/wglext.h>
#include <stdint.h>
#include "math.h"
#include "win32_input.h"

#define global_variable static

//#define WNDWIDTH 1920
//#define WNDHEIGHT 1080

#define WNDWIDTH 1290
#define WNDHEIGHT 760

struct Win32_Platform
{
    HWND hwnd;
    bool app_running;
    Input input;
};

#pragma pack(push, 1)
struct bitmap_header
{
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t bitmapOffset;
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
};
#pragma pack(pop)

struct Texture
{
    uint32_t* pixels;
    int width;
    int height;
    uint32_t id;
};

struct Quad
{
    uint32_t vao;
    int num_indices;
};

Win32_Platform* win32_init_window(HINSTANCE h_instance);
void win32_init_gl_context();
bool win32_process_messages();
Texture load_bmp(const char* filename, bool is_tilesheet);
Input* get_input();
bool* get_app_running();
Quad setup_quad();

#endif

