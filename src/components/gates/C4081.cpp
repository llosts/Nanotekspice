/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4081.cpp
*/

#include "components/gates/C4081.hpp"

namespace nts {
    nts::Tristate C4081::compute(std::size_t pin) {
        // Pin 7 and 14 are power - ignore
        if (pin == 7 || pin == 14)
            return nts::Tristate::Undefined;

        // Gate 1: inputs=1,2 output=3
        if (pin == 3) {
            nts::Tristate a = getLink(1);
            nts::Tristate b = getLink(2);
            return computeAnd(a, b);
        }

        // Gate 2: inputs=5,6 output=4
        if (pin == 4) {
            nts::Tristate a = getLink(5);
            nts::Tristate b = getLink(6);
            return computeAnd(a, b);
        }

        // Gate 3: inputs=8,9 output=10
        if (pin == 10) {
            nts::Tristate a = getLink(8);
            nts::Tristate b = getLink(9);
            return computeAnd(a, b);
        }

        // Gate 4: inputs=12,13 output=11
        if (pin == 11) {
            nts::Tristate a = getLink(12);
            nts::Tristate b = getLink(13);
            return computeAnd(a, b);
        }
        return nts::Tristate::Undefined;
    }

    nts::Tristate C4081::computeAnd(nts::Tristate a, nts::Tristate b) {
        if (a == nts::Tristate::False || b == nts::Tristate::False)
            return nts::Tristate::False;
        if (a == nts::Tristate::True && b == nts::Tristate::True)
            return nts::Tristate::True;
        return nts::Tristate::Undefined;
    }
}
