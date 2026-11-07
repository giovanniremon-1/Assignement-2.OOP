#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Types.h"
#include "OutputDevice.h"

class Memory {
private:
    std::array<uint8_t, 256> cells;
    OutputDevice& output; // Dependency Injection

public:
    explicit Memory(OutputDevice& outDevice) : output(outDevice) {
        clear();
    }

    uint8_t read(uint8_t address) const {
        return cells[address];
    }

    uint16_t read16(uint8_t address) const {
        uint8_t high = cells[address];
        uint8_t low = cells[(address + 1) & 0xFF];
        return static_cast<uint16_t>((high << 8) | low);
    }

    void write(uint8_t address, uint8_t value) {
        cells[address] = value;
        if (address == 0xFF) {
            output.put(value);
        }
    }

    bool loadProgram(uint8_t startAddress, const std::vector<uint8_t>& bytes) {
        if (static_cast<size_t>(startAddress) + bytes.size() > 256) return false;
        for (size_t i = 0; i < bytes.size(); ++i) {
            cells[(startAddress + i) & 0xFF] = bytes[i];
        }
        return true;
    }

    void clear() {
        cells.fill(0);
    }

    void displayMatrix() const {
        std::cout << "\n--- MEMORY DUMP (HEX) ---" << std::endl;
        for (int r = 0; r < 16; ++r) {
            std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (r * 16) << " | ";
            for (int c = 0; c < 16; ++c) {
                std::cout << std::setw(2) << std::setfill('0') << static_cast<int>(cells[r * 16 + c]) << " ";
            }
            std::cout << std::dec << std::endl;
        }
    }
};