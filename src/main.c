#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "engine/engine.h"
#include "platform/platform.h"

int main(void) {
    uint64_t last_ms;
    uint64_t stat_window_start;
    uint64_t run_start;
    uint64_t now_ms;
    uint32_t dt_ms;
    uint32_t sum_dt = 0;
    uint32_t min_dt = UINT32_MAX;
    uint32_t max_dt = 0;
    uint32_t frames = 0;
    char hud[128];

    engine_init();

    last_ms = platform_time_ms();
    stat_window_start = last_ms;
    run_start = last_ms;

    while (!platform_should_close()) {
        now_ms = platform_time_ms();
        dt_ms = (uint32_t)(now_ms - last_ms);
        if (dt_ms > 250u) {
            dt_ms = 250u;
        }
        if (dt_ms == 0u) {
            dt_ms = 1u;
        }
        last_ms = now_ms;

        platform_poll_input();
        engine_step(dt_ms, &g_input);

        platform_begin_frame();
        engine_draw();
        (void)snprintf(hud, sizeof(hud), "FPS: %u  dt: %u ms", frames == 0 ? 0u : (1000u / dt_ms), dt_ms);
        platform_draw_text(10, 10, hud);
        platform_end_frame();

        sum_dt += dt_ms;
        if (dt_ms < min_dt) {
            min_dt = dt_ms;
        }
        if (dt_ms > max_dt) {
            max_dt = dt_ms;
        }
        frames += 1u;

        if ((now_ms - stat_window_start) >= 1000u) {
            const double avg = (frames > 0u) ? ((double)sum_dt / (double)frames) : 0.0;
            printf("[timing] avg=%.2fms min=%ums max=%ums frames=%u\n", avg, min_dt, max_dt, frames);
            sum_dt = 0;
            min_dt = UINT32_MAX;
            max_dt = 0;
            frames = 0;
            stat_window_start = now_ms;
        }

        if ((now_ms - run_start) >= 300000u) {
            printf("[info] 5 minutes elapsed, exiting normally.\n");
            break;
        }
    }

    return 0;
}
