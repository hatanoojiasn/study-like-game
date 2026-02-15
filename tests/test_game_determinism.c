#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "engine/engine.h"
#include "platform/platform.h"

InputState g_input = {0};

typedef struct DrawCapture {
    int x;
    int y;
    int w;
    int h;
    int called;
} DrawCapture;

static DrawCapture g_capture;

uint64_t platform_time_ms(void) { return 0; }
void platform_poll_input(void) {}
int platform_should_close(void) { return 1; }
void platform_begin_frame(void) {}
void platform_end_frame(void) {}

void platform_draw_rect(int x, int y, int w, int h) {
    g_capture.x = x;
    g_capture.y = y;
    g_capture.w = w;
    g_capture.h = h;
    g_capture.called = 1;
}

void platform_draw_text(int x, int y, const char* s) {
    (void)x;
    (void)y;
    (void)s;
}

static DrawCapture simulate_once(const InputState* inputs, size_t count, uint32_t dt_ms) {
    size_t i;
    memset(&g_capture, 0, sizeof(g_capture));
    engine_init();
    for (i = 0; i < count; ++i) {
        engine_step(dt_ms, &inputs[i]);
    }
    engine_draw();
    assert(g_capture.called == 1);
    return g_capture;
}

int main(void) {
    InputState script[120];
    DrawCapture run_a;
    DrawCapture run_b;
    size_t i;

    memset(script, 0, sizeof(script));
    for (i = 0; i < 120; ++i) {
        if (i < 40) {
            script[i].right = 1;
        } else if (i < 80) {
            script[i].down = 1;
        } else {
            script[i].left = 1;
        }
    }

    run_a = simulate_once(script, 120, 16);
    run_b = simulate_once(script, 120, 16);

    assert(run_a.x == run_b.x);
    assert(run_a.y == run_b.y);
    assert(run_a.w == 40);
    assert(run_a.h == 40);

    printf("determinism ok: (%d,%d)\n", run_a.x, run_a.y);
    return 0;
}
