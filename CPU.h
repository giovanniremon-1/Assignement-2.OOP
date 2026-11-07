#pragma once
#include <array>
#include "Types.h"
#include "Memory.h"
#include "ALU.h"

class CPU {
private:
    std::array<uint8_t, 16> registers;
    uint8_t pc;
    uint16_t ir;
    bool halted;

    uint16_t fetch(Memory& mem) {
        uint16_t instructionBytes = mem.read16(pc);
        pc += 2;
        return instructionBytes;
    }

    Instruction decode(uint16_t raw) const {
        Instruction ins;
        ins.opcode = static_cast<Opcode>((raw >> 12) & 0xF);
        ins.r = (raw >> 8) & 0xF;
        ins.s = (raw >> 4) & 0xF;
        ins.t = raw & 0xF;
        ins.xy = raw & 0xFF;
        return ins;
    }

    StepResult execute(const Instruction& ins, Memory& mem) {
        switch (ins.opcode) {
            case Opcode::LOAD_MEM:  registers[ins.r] = mem.read(ins.xy); break;
            case Opcode::LOAD_IMM:  registers[ins.r] = ins.xy; break;
            case Opcode::STORE:     mem.write(ins.xy, registers[ins.r]); break;
            case Opcode::MOVE:      registers[ins.t] = registers[ins.s]; break;
            case Opcode::ADD_INT:   registers[ins.r] = ALU::addTwosComplement(registers[ins.s], registers[ins.t]); break;
            case Opcode::ADD_FLOAT: registers[ins.r] = ALU::addFloat(registers[ins.s], registers[ins.t]); break;
            case Opcode::OR:        registers[ins.r] = ALU::bitOr(registers[ins.s], registers[ins.t]); break;
            case Opcode::AND:       registers[ins.r] = ALU::bitAnd(registers[ins.s], registers[ins.t]); break;
            case Opcode::XOR:       registers[ins.r] = ALU::bitXor(registers[ins.s], registers[ins.t]); break;
            case Opcode::ROTATE:    registers[ins.r] = ALU::rotateRight(registers[ins.r], ins.t); break;
            case Opcode::JUMP_EQ:   if (registers[ins.r] == registers[0]) pc = ins.xy; break;
            case Opcode::HALT:      halted = true; return StepResult::HALTED;
            case Opcode::JUMP_GT:   if (registers[ins.r] > registers[0]) pc = ins.xy; break;
            default: return StepResult::INVALID_OPCODE;
        }
        return StepResult::OK;
    }

public:
    CPU() { reset(0x00); }

    StepResult step(Memory& mem) {
        if (halted) return StepResult::HALTED;
        ir = fetch(mem);
        Instruction ins = decode(ir);
        return execute(ins, mem);
    }

    void reset(uint8_t startAddress) {
        registers.fill(0);
        pc = startAddress;
        ir = 0;
        halted = false;
    }

    bool isHalted() const { return halted; }
    uint8_t getPC() const { return pc; }
    uint16_t getIR() const { return ir; }
    uint8_t getRegister(uint8_t index) const { return registers[index]; }
};