/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4512.cpp
*/

#include "components/advanced/C4512.hpp"

namespace nts {
    nts::Tristate C4512::compute(std::size_t pin) {
        if (pin == 8 || pin == 16)
            return Tristate::Undefined;

        
        if (pin == 14) {
            nts::Tristate inhibit = getLink(10);
            nts::Tristate enable = getLink(15);

            // OE has highest priority: True → Hi-Z output
            if (enable == Tristate::True)
                return Tristate::Undefined;

            // If inhibited, output is 0
            if (inhibit == Tristate::True)
                return Tristate::False;

            // If inhibit is Undefined, output is Undefined
            if (inhibit == Tristate::Undefined)
                return Tristate::Undefined;

            nts::Tristate a = getLink(11);
            nts::Tristate b = getLink(12);
            nts::Tristate c = getLink(13);

            if (a == Tristate::Undefined || b == Tristate::Undefined || c == Tristate::Undefined)
                return Tristate::Undefined;

            int addr = ((c == Tristate::True) ? 4 : 0) +
                       ((b == Tristate::True) ? 2 : 0) +
                       ((a == Tristate::True) ? 1 : 0);

            // Input pins for addresses 0-7
            const int inputPins[8] = {1, 2, 3, 4, 5, 6, 7, 9};
            return getLink(inputPins[addr]);
        }

        return Tristate::Undefined;
    }
}
