#include "engine/engine.h"

#include "game/game.h"

void engine_init(void) {
    game_init();
}

void engine_step(uint32_t dt_ms, const InputState* in) {
    game_step(dt_ms, in);
}

void engine_draw(void) {
    game_draw();
}
