/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4094.cpp
*/

#include "components/advanced/C4094.hpp"

namespace nts {
    void C4094::simulate(std::size_t tick) {
        (void)tick;

        nts::Tristate clock = getLink(3);
        nts::Tristate data = getLink(2);

        // Capture Q'S (out_qe) on FALLING edge
        if (clock == Tristate::False && _lastClock == Tristate::True) {
            _qe = _register[7]; // Q'S latches QS on falling edge (NOT inverted)
        }
    
        // Shift on positive clock edge
        if (clock == Tristate::True && _lastClock != Tristate::True) {
            for (int i = 7; i > 0; i--)
                _register[i] = _register[i - 1];
            _register[0] = data;
        }

        _lastClock = clock;
    }

    nts::Tristate C4094::compute(std::size_t pin) {
        if (pin == 8 || pin == 16)
            return Tristate::Undefined;

        nts::Tristate oe = getLink(15);

        const size_t outputPins[8] = {4, 5, 6, 7, 14, 13, 12, 11};
        
        for (int i = 0; i < 8; i++) {
            if (pin == outputPins[i]) {
                if (oe == Tristate::True)
                    return _register[i];
                return Tristate::Undefined;
            }
        }

        // Serial outputs
        if (pin == 9)
            return _register[7];    // QS  = register[7]
        if (pin == 10)              // Q'S = captured on falling edge (NOT the inverse of QS)
            return _qe;

        return Tristate::Undefined;
    }
}
