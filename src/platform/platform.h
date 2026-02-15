#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

typedef struct InputState {
    int up;
    int down;
    int left;
    int right;
    int action;
} InputState;

extern InputState g_input;

uint64_t platform_time_ms(void);
void platform_poll_input(void);
int platform_should_close(void);
void platform_begin_frame(void);
void platform_draw_rect(int x, int y, int w, int h);
void platform_draw_text(int x, int y, const char* s);
void platform_end_frame(void);

#endif
