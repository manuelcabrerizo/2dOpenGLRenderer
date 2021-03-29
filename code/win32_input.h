#ifndef WIN32INPUT_H
#define WIN32INPUT_H

#include <stdint.h>

struct Input
{
    bool keys_down[256];
    bool keys_up[256];
};

void set_keydown(uint32_t key_code, Input* input);
void set_keyup(uint32_t key_code, Input* input);
bool key_down(uint32_t key_code, Input* input);
bool keys_up(uint32_t key_code, Input* input);


#endif
