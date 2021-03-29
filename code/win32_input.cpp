#include "win32_input.h"

void set_keydown(uint32_t key_code, Input* input)
{
    input->keys_down[key_code] = true;
    input->keys_up[key_code] = false;
}

void set_keyup(uint32_t key_code, Input* input)
{
    input->keys_down[key_code] = false;
    input->keys_up[key_code] = true;
}

bool key_down(uint32_t key_code, Input* input)
{
    return input->keys_down[key_code];
}

bool keys_up(uint32_t key_code, Input* input)
{
    return input->keys_up[key_code];
}
