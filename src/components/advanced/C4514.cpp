/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4514.cpp
*/

#include "components/advanced/C4514.hpp"

namespace nts {
    const size_t outputPins[16] = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};

    bool C4514::isOutputPin(std::size_t pin) {
        for (int i = 0; i < 16; i++) {
            if (pin == outputPins[i])
                return true;
        }
        return false;
    }

    void C4514::simulate(std::size_t tick) {
        (void)tick;
    }

    nts::Tristate C4514::compute(std::size_t pin) {
        if (pin == 12 || pin == 24)
            return Tristate::Undefined;

        if (!isOutputPin(pin))
            return Tristate::Undefined;

        // Inhibit HIGH forces all outputs LOW
        nts::Tristate inhibit = getLink(23);
        if (inhibit == Tristate::True)
            return Tristate::False;

        // Decode address directly from inputs (Undefined treated as 0/False)
        nts::Tristate a0 = getLink(2);
        nts::Tristate a1 = getLink(3);
        nts::Tristate a2 = getLink(21);
        nts::Tristate a3 = getLink(22);

        if (a0 == Tristate::Undefined || a1 == Tristate::Undefined ||
                a2 == Tristate::Undefined || a3 == Tristate::Undefined)
            return Tristate::Undefined;

        int addr = ((a3 == Tristate::True) ? 8 : 0) +
                   ((a2 == Tristate::True) ? 4 : 0) +
                   ((a1 == Tristate::True) ? 2 : 0) +
                   ((a0 == Tristate::True) ? 1 : 0);

        for (int i = 0; i < 16; i++) {
            if (pin == outputPins[i])
                return (i == addr) ? Tristate::True : Tristate::False;
        }

        return Tristate::Undefined;
    }
}
