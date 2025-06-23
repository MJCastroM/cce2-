#include <stdint.h>
#include <vector>
#include <iostream>
#include "gf256.h"

extern void euclid(const std::vector<uint8_t>& syndromes, int max_deg,
                   std::vector<uint8_t>& sigma, std::vector<uint8_t>& omega);
extern void print_poly(const std::vector<uint8_t>& p, const char* name);

int main() {
    const int N = 64, K = 56, R = 8;
    uint8_t received[N] = {
        0x71, 0x75, 0x65, 0x20, 0x70, 0x61, 0x73, 0x61,
        0x3F, 0x20, 0x74, 0x6F, 0x78, 0x64, 0x6F, 0x20,
        0x62, 0x69, 0x65, 0x6E, 0x3F, 0x20, 0x73, 0x69,
        0x20, 0x73, 0x69, 0x20, 0x73, 0x69, 0x20, 0x6E,
        0x6F, 0x20, 0x6E, 0x6F, 0x20, 0x6E, 0x6F, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x91, 0xE4, 0x93, 0x80, 0x96, 0x20, 0x24, 0x20
    };

    std::vector<uint8_t> syndromes(R, 0);
    for (int i = 0; i < R; ++i) {
        uint8_t s = 0;
        for (int j = 0; j < N; ++j) {
            uint8_t pow = gfpow(1, (i + 1) * j);  // α^((i+1)·j)
            s ^= gfmul(received[j], pow);
        }
        syndromes[i] = s;
    }

    std::vector<uint8_t> sigma, omega;
    euclid(syndromes, R, sigma, omega);

    print_poly(syndromes, "S(x)");
    print_poly(sigma, "Lambda(x)");
    print_poly(omega, "Omega(x)");

    return 0;
}
