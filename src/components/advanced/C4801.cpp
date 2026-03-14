/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4801.cpp
*/

#include "components/advanced/C4801.hpp"

namespace nts {
    static const size_t ADDR_PINS[10] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
    static const size_t DATA_PINS[8] = {9, 10, 11, 13, 14, 15, 16, 17};

    int C4801::readAddress(void) {
        int addr = 0;
        for (int i = 0; i < 10; i++) {
            nts::Tristate bit = getLink(ADDR_PINS[i]);
            if (bit == nts::Tristate::True)
                addr |= (1 << i);
        }
        return addr;
    }

    void C4801::simulate(std::size_t tick) {
        (void)tick;

        nts::Tristate cs = getLink(18); // active low
        nts::Tristate oe = getLink(20); // active low
        nts::Tristate we = getLink(21); // active low

        // Only deselect if cs is EXPLICITLY high
        if (cs == Tristate::True) {
            for (int i = 0; i < 8; i++)
                _dataPins[i] = Tristate::Undefined;
            return;
        }

        int addr = readAddress();

        if (we == Tristate::False) {
            // Write mode: read data from input links and store in memory
            unsigned char byte = 0;
            for (int i = 0; i < 8; i++) {
                nts::Tristate bit = getLinkDirect(DATA_PINS[i]);
                if (bit == Tristate::True)
                    byte |= (1 << i);
            }
            _memory[addr] = byte;
            // In write mode the data bus is driven by the master, not the RAM
            for (int i = 0; i < 8; i++)
                _dataPins[i] = Tristate::Undefined;
        } else if (oe == Tristate::False) {
            // Read mode: drive data bus from memory
            unsigned char byte = _memory[addr];
            for (int i = 0; i < 8; i++)
                _dataPins[i] = (byte & (1 << i)) ? Tristate::True : Tristate::False;
        } else {
            // Neither WE nor OE active: bus floating
            for (int i = 0; i < 8; i++)
                _dataPins[i] = Tristate::Undefined;
        }
    }

    nts::Tristate C4801::compute(std::size_t pin) {
        if (pin == 12 || pin == 19 || pin == 24)
            return Tristate::Undefined;

        for (int i = 0; i < 8; i++) {
            if (pin == DATA_PINS[i])
                return _dataPins[i];
        }

        return Tristate::Undefined;
    }
}
