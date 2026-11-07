#pragma once
#include <iostream>
#include "VoleMachine.h"

class SimulatorUI {
private:
    VoleMachine machine;

public:
    void start() {
        int choice;
        while (true) {
            std::cout << "\n=== Vole Machine (FCAI-CU) ===\n1. Load File\n2. Run\n3. Step\n4. Status\n5. Reset\n6. Exit\nChoice: ";
            if (!(std::cin >> choice)) break;
            if (choice == 1) {
                std::string file; uint8_t addr;
                std::cout << "Filename: "; std::cin >> file;
                std::cout << "Start Address (hex): "; 
                int a; std::cin >> std::hex >> a >> std::dec;
                if (machine.loadProgramFile(file, static_cast<uint8_t>(a))) std::cout << "Loaded!\n";
                else std::cout << "Error loading file.\n";
            } else if (choice == 2) {
                machine.run();
            } else if (choice == 3) {
                machine.step();
                machine.showStatus();
            } else if (choice == 4) {
                machine.showStatus();
            } else if (choice == 5) {
                machine.reset();
                std::cout << "Reset.\n";
            } else if (choice == 6) {
                break;
            }
        }
    }
};