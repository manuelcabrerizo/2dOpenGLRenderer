#include <stdint.h>
#include "win32_utility.h"
#include "win32_app.h"
#include "renderer.h"

int WinMain(HINSTANCE h_instance,
            HINSTANCE h_prev_instance,
            LPSTR     lp_cmd_line,
            int       n_cmd_show)
{

    Win32_Platform* platform = win32_init_window(h_instance);
    LARGE_INTEGER perfCountFrequency;
    QueryPerformanceFrequency(&perfCountFrequency);
    uint64_t frequency = (uint64_t)perfCountFrequency.QuadPart;

    if(platform->hwnd)
    {
        platform->app_running = true;
        ShowWindow(platform->hwnd, SW_SHOW);
        CoInitialize(nullptr);
        LARGE_INTEGER lastCounter;
        QueryPerformanceCounter(&lastCounter);

        win32_init_gl_context();
        HDC device_context = GetDC(platform->hwnd);
        setup_renderer();
        win32_start();
        
        while(platform->app_running == true)
        {
            static float lastTime = (float)timeGetTime();
            if(!win32_process_messages())
            {
                LARGE_INTEGER endCounter;
                QueryPerformanceCounter(&endCounter);
                uint64_t counterElapsed =  endCounter.QuadPart - lastCounter.QuadPart; 
                float delta_time = (counterElapsed / (float)frequency); 

                glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                win32_update(delta_time);
                win32_render();

                SwapBuffers(device_context);
                lastCounter = endCounter;  
            }
        }
        ReleaseDC(platform->hwnd, device_context); 
    }
    else
    {
        return 1;
    }
    return 0;
}





