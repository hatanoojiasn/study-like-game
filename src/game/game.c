#include "game/game.h"

#include <stdio.h>

#include "platform/platform.h"

typedef struct GameState {
    float x;
    float y;
    float speed_px_per_s;
} GameState;

static GameState g_game;

void game_init(void) {
    g_game.x = 100.0f;
    g_game.y = 100.0f;
    g_game.speed_px_per_s = 200.0f;
}

void game_step(uint32_t dt_ms, const InputState* in) {
    const float dt_sec = (float)dt_ms / 1000.0f;
    float vx = 0.0f;
    float vy = 0.0f;

    if (in != NULL) {
        if (in->left) {
            vx -= 1.0f;
        }
        if (in->right) {
            vx += 1.0f;
        }
        if (in->up) {
            vy -= 1.0f;
        }
        if (in->down) {
            vy += 1.0f;
        }
    }

    g_game.x += vx * g_game.speed_px_per_s * dt_sec;
    g_game.y += vy * g_game.speed_px_per_s * dt_sec;

    if (g_game.x < 0.0f) {
        g_game.x = 0.0f;
    }
    if (g_game.y < 0.0f) {
        g_game.y = 0.0f;
    }
    if (g_game.x > 760.0f) {
        g_game.x = 760.0f;
    }
    if (g_game.y > 560.0f) {
        g_game.y = 560.0f;
    }
}

void game_draw(void) {
    char hud[128];
    const int px = (int)(g_game.x + 0.5f);
    const int py = (int)(g_game.y + 0.5f);

    platform_draw_rect(px, py, 40, 40);
    (void)snprintf(hud, sizeof(hud), "Player: (%d, %d)", px, py);
    platform_draw_text(10, 40, hud);
}
