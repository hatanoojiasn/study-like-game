#include "platform/platform.h"

#include <raylib.h>

InputState g_input = {0};

static int g_initialized = 0;

static void ensure_initialized(void) {
    if (!g_initialized) {
        InitWindow(800, 600, "Study Like Game - Quest 0");
        SetTargetFPS(60);
        g_initialized = 1;
    }
}

uint64_t platform_time_ms(void) {
    return (uint64_t)(GetTime() * 1000.0);
}

void platform_poll_input(void) {
    ensure_initialized();

    g_input.up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
    g_input.down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);
    g_input.left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    g_input.right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
    g_input.action = IsKeyDown(KEY_SPACE);
}

int platform_should_close(void) {
    ensure_initialized();
    return WindowShouldClose();
}

void platform_begin_frame(void) {
    ensure_initialized();
    BeginDrawing();
    ClearBackground((Color){20, 20, 28, 255});
}

void platform_draw_rect(int x, int y, int w, int h) {
    DrawRectangle(x, y, w, h, SKYBLUE);
}

void platform_draw_text(int x, int y, const char* s) {
    DrawText(s, x, y, 20, RAYWHITE);
}

void platform_end_frame(void) {
    EndDrawing();
}
