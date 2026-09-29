#include "raw_hat_binding.h"

#include <cassert>
#include <cstring>

int main() {
    assert(recomp_raw_hat_encode(0, 1) == 128);
    assert(recomp_raw_hat_encode(0, 2) == 129);
    assert(recomp_raw_hat_encode(0, 4) == 130);
    assert(recomp_raw_hat_encode(0, 8) == 131);
    assert(recomp_raw_hat_encode(15, 8) == 191);
    assert(recomp_raw_hat_encode(0, 3) == -1); // diagonal is not a bind target
    assert(recomp_raw_hat_encode(16, 1) == -1);
    assert(recomp_raw_hat_index(127) == -1);
    assert(recomp_raw_hat_index(191) == 15);
    assert(recomp_raw_hat_value(131) == 8);
    assert(std::strcmp(recomp_raw_hat_direction(130), "Down") == 0);
}
