#include "win32_utility.h"
#include <stdio.h>
#include <stdlib.h>

global_variable Win32_Platform platform;

LRESULT CALLBACK window_proc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result;
    switch(Msg)
    {
        case WM_CLOSE:
        {
            platform.app_running = FALSE;
        }break;
        case WM_DESTROY:
        {
            platform.app_running = FALSE;
        }break;
        case WM_KEYDOWN:
        {
            uint32_t key_code = (uint32_t)wParam;
            set_keydown(key_code, &platform.input);
        }break;
        case WM_KEYUP:
        {
            uint32_t key_code = (uint32_t)wParam;
            set_keyup(key_code, &platform.input);
        }break;
        default:
        {
            result = DefWindowProc(hwnd, Msg, wParam, lParam); 
        }break;
    }
    return(result);
}

Input* get_input()
{
    return &platform.input;
}

Win32_Platform* win32_init_window(HINSTANCE h_instance)
{
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = window_proc;
    wc.hInstance     = h_instance; 
    wc.lpszClassName = "FrameClass";

    if(!RegisterClassA(&wc))
    {
        OutputDebugString("FAILED register class\n");    
    }
    
    RECT wr;
	wr.left = 0;
	wr.right = WNDWIDTH;
	wr.top = 0;
	wr.bottom = WNDHEIGHT;
	AdjustWindowRect(&wr, WS_OVERLAPPED, FALSE);

    platform.hwnd = CreateWindowA("FrameClass", "Role3DGame",
                  WS_OVERLAPPEDWINDOW,
                  0, 0,
                  wr.right - wr.left, wr.bottom - wr.top,
                  NULL, NULL,
                  h_instance,
                  NULL);
    return &platform;
}


bool win32_process_messages()
{
    MSG  msg;
    if(PeekMessageA(&msg, platform.hwnd, 0, 0, PM_REMOVE))
    {            
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
        return true;
    }
    return false;
}

void win32_init_gl_context()
{
    PIXELFORMATDESCRIPTOR pfd =
    {
	    sizeof(PIXELFORMATDESCRIPTOR),
	    1,
	    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
	    PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
	    32,                   // Colordepth of the framebuffer.
	    0, 0, 0, 0, 0, 0,
	    0,
	    0,
	    0,
	    0, 0, 0, 0,
	    24,                   // Number of bits for the depthbuffer
	    8,                    // Number of bits for the stencilbuffer
	    0,                    // Number of Aux buffers in the framebuffer.
	    PFD_MAIN_PLANE,
	    0,
	    0, 0, 0
    };
    // create openg gl context in win32 
    HDC device_context = GetDC(platform.hwnd);
    
    int pixel_format = ChoosePixelFormat(device_context, &pfd);
    SetPixelFormat(device_context, pixel_format, &pfd);
    HGLRC opengl_render_context_temp = wglCreateContext(device_context);
    wglMakeCurrent(device_context, opengl_render_context_temp);
      
    int attributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };
        
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = 
        (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    HGLRC opengl_render_context;
    if(wglCreateContextAttribsARB)
    {
        opengl_render_context = wglCreateContextAttribsARB(device_context, NULL, attributes);
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(opengl_render_context_temp);
        wglMakeCurrent(device_context, opengl_render_context);

        PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = 
            (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
        wglSwapIntervalEXT(1);
    }

    if(!gladLoadGL())
    {
        OutputDebugString("ERROR::INITIALIZING::GLAD\n");
    }

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glViewport(0, 0, WNDWIDTH, WNDHEIGHT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);  
}

Texture load_bmp(const char* filename, bool is_tilesheet)
{
    bitmap_header header;
    Texture texture;
    FILE* file = fopen(filename, "rb");
    if(file != NULL)
    {
        fread(&header, sizeof(header), 1, file);
        texture.pixels = (uint32_t*)malloc(sizeof(uint32_t) * header.width * header.height);
        fseek(file, header.bitmapOffset, SEEK_SET);
        fread(texture.pixels, sizeof(uint32_t), header.width * header.height, file);
        texture.width = header.width;
        texture.height = header.height;
    }
    fclose(file);
    if(!is_tilesheet)
    {
        glGenTextures(1, &texture.id);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        if(texture.pixels != NULL)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height,
                                        0, GL_BGRA, GL_UNSIGNED_BYTE, texture.pixels);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    return(texture);
}

Quad setup_quad()
{
    Quad quad;

    float quad_vertices[] = {
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f,   
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   
       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   
       -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  
    };
    unsigned int quad_indices[] = {  
        0, 1, 3,   
        1, 2, 3    
    };
    
    quad.num_indices = 6; 
    glGenVertexArrays(1, &quad.vao);
    glBindVertexArray(quad.vao);
    uint32_t VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    uint32_t EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), quad_indices, GL_STATIC_DRAW); 
    glBindVertexArray(0);
    OutputDebugString("quad cargador!!!\n");
    return quad;
}

