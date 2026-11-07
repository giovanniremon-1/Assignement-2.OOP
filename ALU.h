#pragma once
#include <cstdint>

class ALU {
public:
    static uint8_t addTwosComplement(uint8_t a, uint8_t b) {
        return static_cast<uint8_t>(a + b);
    }

    static uint8_t addFloat(uint8_t a, uint8_t b) {
        int s1 = (a >> 7) & 1, e1 = (a >> 4) & 7, m1 = a & 0xF;
        int s2 = (b >> 7) & 1, e2 = (b >> 4) & 7, m2 = b & 0xF;
        
        int val1 = (s1 ? -((m1 | 16) >> (7 - e1)) : ((m1 | 16) >> (7 - e1)));
        int val2 = (s2 ? -((m2 | 16) >> (7 - e2)) : ((m2 | 16) >> (7 - e2)));
        int res = val1 + val2;

        int resSign = (res < 0) ? 1 : 0;
        if (res < 0) res = -res;
        int expOut = 4;
        while (res > 15 && expOut < 7) { res >>= 1; expOut++; }

        return static_cast<uint8_t>((resSign << 7) | ((expOut & 7) << 4) | (res & 0xF));
    }

    static uint8_t bitOr(uint8_t a, uint8_t b) { return a | b; }
    static uint8_t bitAnd(uint8_t a, uint8_t b) { return a & b; }
    static uint8_t bitXor(uint8_t a, uint8_t b) { return a ^ b; }

    static uint8_t rotateRight(uint8_t value, uint8_t steps) {
        steps %= 8;
        return static_cast<uint8_t>((value >> steps) | (value << (8 - steps)));
    }
};