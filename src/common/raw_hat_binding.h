#ifndef RECOMP_RAW_HAT_BINDING_H
#define RECOMP_RAW_HAT_BINDING_H

/* Raw wheel button bindings are 0..127. Reserve 128..191 for the four
 * cardinal directions of up to 16 POV hats without changing old configs. */
enum { RECOMP_RAW_HAT_BASE = 128, RECOMP_RAW_HAT_MAX = 191 };

static inline int recomp_raw_hat_encode(int hat, int value) {
    if (hat < 0 || hat >= 16) return -1;
    int direction = value == 1 ? 0 : value == 2 ? 1 :
                    value == 4 ? 2 : value == 8 ? 3 : -1;
    return direction < 0 ? -1 : RECOMP_RAW_HAT_BASE + hat * 4 + direction;
}

static inline int recomp_raw_hat_index(int binding) {
    return binding >= RECOMP_RAW_HAT_BASE && binding <= RECOMP_RAW_HAT_MAX
        ? (binding - RECOMP_RAW_HAT_BASE) / 4 : -1;
}

static inline int recomp_raw_hat_value(int binding) {
    if (recomp_raw_hat_index(binding) < 0) return 0;
    return 1 << ((binding - RECOMP_RAW_HAT_BASE) % 4);
}

static inline const char *recomp_raw_hat_direction(int binding) {
    switch (recomp_raw_hat_value(binding)) {
    case 1: return "Up";
    case 2: return "Right";
    case 4: return "Down";
    case 8: return "Left";
    default: return "Unknown";
    }
}

#endif
