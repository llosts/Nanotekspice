/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4017.cpp
*/

#include "components/advanced/C4017.hpp"

namespace nts {
    void C4017::simulate(std::size_t tick) {
        (void)tick;

        nts::Tristate cp0 = getLink(14);   // CP0: rising-edge clock input
        nts::Tristate cp1 = getLink(13);   // CP1: clock enable inhibit (active LOW = enabled)
        nts::Tristate reset = getLink(15); // MR: master reset (active HIGH)

        // Reset has priority
        if (reset == Tristate::True) {
            _counter = 0;
            _lastCP0 = cp0;
            _lastCP1 = cp1;
            return;
        }

        // Mode 1: Rising edge of CP0 while CP1 is LOW
        if (cp1 != Tristate::True && cp0 == Tristate::True && _lastCP0 != Tristate::True) {
            _counter = (_counter + 1) % 10;
        }
        // Mode 2: Rising edge of CP1 (clock enable) while CP0 is HIGH
        else if (cp1 == Tristate::False && _lastCP1 == Tristate::True && cp0 == Tristate::True) {
            _counter = (_counter + 1) % 10;
        }
        
        _lastCP0 = cp0;
        _lastCP1 = cp1;
    }

    nts::Tristate C4017::compute(std::size_t pin) {
        if (pin == 8 || pin == 16)
            return Tristate::Undefined;

        const size_t outputPins[10] = {3, 2, 4, 7, 10, 1, 5, 6, 9, 11};
        
        for (int i = 0; i < 10; i++) {
            if (pin == outputPins[i])
                return (_counter == i) ? Tristate::True : Tristate::False;
        }

        // Pin 12 is carry out (high for states 0-4)
        if (pin == 12)
            return (_counter < 5) ? Tristate::True : Tristate::False;

        return Tristate::Undefined;
    }
}
