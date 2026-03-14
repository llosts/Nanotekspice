/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C2716.cpp
*/

#include <fstream>
#include <iostream>

#include "components/advanced/C2716.hpp"

namespace nts {
    static const size_t ROM_ADDR_PINS[11] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19};
    static const size_t ROM_DATA_PINS[8] = {9, 10, 11, 13, 14, 15, 16, 17};

    void C2716::loadROM(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Warning: Could not open " << filename << ", ROM will be empty" << std::endl;
            return;
        }

        file.read(reinterpret_cast<char*>(_memory.data()), 2048);
        file.close();
    }

    int C2716::readAddress() {
        int addr = 0;
        for (int i = 0; i < 11; i++) {
            nts::Tristate bit = getLink(ROM_ADDR_PINS[i]);
            if (bit == nts::Tristate::Undefined)
                return -1;
            if (bit == nts::Tristate::True)
                addr |= (1 << i);
        }
        return addr;
    }

    nts::Tristate C2716::compute(std::size_t pin) {
        if (pin == 12 || pin == 24)
            return Tristate::Undefined;

        for (int i = 0; i < 8; i++) {
            if (pin == ROM_DATA_PINS[i]) {
                nts::Tristate ce = getLink(18);
                nts::Tristate oe = getLink(20);

                if (ce != Tristate::False || oe != Tristate::False)
                    return Tristate::Undefined;

                int addr = readAddress();
                if (addr < 0)
                    return Tristate::Undefined;

                return (_memory[addr] & (1 << i)) ? Tristate::True : Tristate::False;
            }
        }

        return Tristate::Undefined;
    }
}
