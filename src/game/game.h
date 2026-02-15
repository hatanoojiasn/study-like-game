#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "platform/platform.h"

void game_init(void);
void game_step(uint32_t dt_ms, const InputState* in);
void game_draw(void);

#endif
