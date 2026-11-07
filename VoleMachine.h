#pragma once
#include "Memory.h"
#include "CPU.h"
#include "ProgramLoader.h"

class VoleMachine {
private:
    ConsoleOutput output;
    Memory memory;
    CPU cpu;
    size_t maxSteps;

public:
    explicit VoleMachine(size_t maxStp = 10000) : memory(output), maxSteps(maxStp) {}

    bool loadProgramFile(const std::string& fileName, uint8_t startAddress) {
        auto bytesOpt = ProgramLoader::parseFile(fileName);
        if (!bytesOpt) return false;
        cpu.reset(startAddress);
        memory.clear();
        return memory.loadProgram(startAddress, *bytesOpt);
    }

    StepResult step() { return cpu.step(memory); }

    StepResult run() {
        size_t steps = 0;
        StepResult result = StepResult::OK;
        while (!cpu.isHalted() && steps < maxSteps) {
            result = step();
            if (result != StepResult::OK) break;
            steps++;
        }
        output.flush();
        return result;
    }

    void reset() {
        cpu.reset(0x00);
        memory.clear();
    }

    void showStatus() const {
        std::cout << "\n[CPU Status] PC: 0x" << std::hex << std::uppercase << (int)cpu.getPC() 
             << " | IR: 0x" << cpu.getIR() << std::dec << " | Halted: " << (cpu.isHalted() ? "YES" : "NO") << std::endl;
        memory.displayMatrix();
    }
};