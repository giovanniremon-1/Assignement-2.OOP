#pragma once
#include <iostream>
#include <string>
#include <cstdint>

class OutputDevice {
public:
    virtual ~OutputDevice() = default;
    virtual void put(uint8_t value) = 0;
    virtual void flush() = 0;
};

class ConsoleOutput : public OutputDevice {
private:
    std::string buffer;

public:
    void put(uint8_t value) override {
        buffer += static_cast<char>(value);
    }

    void flush() override {
        std::cout << "[Output]: " << buffer << std::endl;
        buffer.clear();
    }
};