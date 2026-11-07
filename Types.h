#pragma once
#include <cstdint>

enum class Opcode : uint8_t {
    LOAD_MEM   = 0x1,
    LOAD_IMM   = 0x2,
    STORE      = 0x3,
    MOVE       = 0x4,
    ADD_INT    = 0x5,
    ADD_FLOAT  = 0x6,
    OR         = 0x7,
    AND        = 0x8,
    XOR        = 0x9,
    ROTATE     = 0xA,
    JUMP_EQ    = 0xB,
    HALT       = 0xC,
    JUMP_GT    = 0xD
};

enum class StepResult {
    OK,
    HALTED,
    INVALID_OPCODE,
    STEP_LIMIT_REACHED
};

struct Instruction {
    Opcode opcode;
    uint8_t r;
    uint8_t s;
    uint8_t t;
    uint8_t xy;
};