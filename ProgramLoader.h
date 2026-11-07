#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <optional>
#include <cstdint>

class ProgramLoader {
public:
    static std::optional<std::vector<uint8_t>> parseFile(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) return std::nullopt;

        std::vector<uint8_t> bytes;
        std::string token;
        while (file >> token) {
            try {
                size_t idx;
                int val = std::stoi(token, &idx, 16);
                if (idx == token.size() && val >= 0 && val <= 255) {
                    bytes.push_back(static_cast<uint8_t>(val));
                }
            } catch (...) {}
        }
        return bytes;
    }
};