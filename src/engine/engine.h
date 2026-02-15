#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include "platform/platform.h"

void engine_init(void);
void engine_step(uint32_t dt_ms, const InputState* in);
void engine_draw(void);

#endif
