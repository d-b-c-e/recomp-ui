#pragma once

#include <cstdint>
#include <cstring>

/* Raw joystick capture must ignore a control that was already down when the
 * user clicked Bind. A noisy/stuck button can then remain visible in the live
 * monitor without stealing every unrelated binding. Its next fresh press is
 * eligible after an observed release. */
struct RawButtonCaptureGate {
    uint8_t blocked[128]{};

    void begin(const uint8_t* pressed, int count) {
        std::memset(blocked, 0, sizeof(blocked));
        if (!pressed || count <= 0) return;
        if (count > 128) count = 128;
        for (int i = 0; i < count; ++i) blocked[i] = pressed[i] ? 1 : 0;
    }

    void released(int button) {
        if (button >= 0 && button < 128) blocked[button] = 0;
    }

    bool accepts_down(int button) const {
        return button >= 0 && button < 128 && !blocked[button];
    }

    bool was_held(int button) const {
        return button >= 0 && button < 128 && blocked[button];
    }
};
