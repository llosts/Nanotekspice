/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4040.cpp
*/

#include "components/advanced/C4040.hpp"

namespace nts {
    void C4040::simulate(std::size_t tick) {
        (void)tick;

        nts::Tristate clock = getLink(10);
        nts::Tristate reset = getLink(11);

        // Reset has priority
        if (reset == Tristate::True) {
            _count = 0;
            _lastClock = clock;
            return;
        }

        // Falling edge increment counter
        if (clock == Tristate::False && _lastClock == Tristate::True)
            _count = (_count + 1) & 0xFFF;

        _lastClock = clock;
    }

    nts::Tristate C4040::compute(std::size_t pin) {
        if (pin == 8 || pin == 16)
            return Tristate::Undefined;

        const size_t outputMap[12] = {9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1};
        
        for (int i = 0; i < 12; i++) {
            if (pin == outputMap[i])
                return ((_count >> i) & 1) ? Tristate::True : Tristate::False;
        }

        return Tristate::Undefined;
    }
}
