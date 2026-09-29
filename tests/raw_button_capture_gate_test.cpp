#include "raw_button_capture_gate.h"

#include <cassert>
#include <cstdint>

int main() {
    RawButtonCaptureGate gate;
    uint8_t held[128]{};
    held[12] = 1;  // a paddle/switch already active when Bind is clicked
    gate.begin(held, 128);
    assert(gate.was_held(12));
    assert(!gate.accepts_down(12));
    assert(gate.accepts_down(0));
    assert(gate.accepts_down(127));
    assert(!gate.accepts_down(-1));
    assert(!gate.accepts_down(128));
    gate.released(12);
    assert(gate.accepts_down(12));
    gate.begin(nullptr, 0);
    assert(gate.accepts_down(12));
}
