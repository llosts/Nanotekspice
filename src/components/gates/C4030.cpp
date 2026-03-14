/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4030.cpp
*/

#include "components/gates/C4030.hpp"

namespace nts {
    nts::Tristate C4030::compute(std::size_t pin) {
        if (pin == 7 || pin == 14)
            return nts::Tristate::Undefined;

        if (pin == 3) return computeXor(getLink(1), getLink(2));
        if (pin == 4) return computeXor(getLink(5), getLink(6));
        if (pin == 10) return computeXor(getLink(8), getLink(9));
        if (pin == 11) return computeXor(getLink(12), getLink(13));

        return nts::Tristate::Undefined;
    }

    nts::Tristate C4030::computeXor(nts::Tristate a, nts::Tristate b) {
        if (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined)
            return nts::Tristate::Undefined;
        return (a != b) ? nts::Tristate::True : nts::Tristate::False;
    }
}
