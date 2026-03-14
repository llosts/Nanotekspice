/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4071.cpp
*/

#include "components/gates/C4071.hpp"

namespace nts {
    nts::Tristate C4071::compute(std::size_t pin)
    {
        if (pin == 7 || pin == 14)
            return nts::Tristate::Undefined;

        if (pin == 3) return computeOr(getLink(1), getLink(2));
        if (pin == 4) return computeOr(getLink(5), getLink(6));
        if (pin == 10) return computeOr(getLink(8), getLink(9));
        if (pin == 11) return computeOr(getLink(12), getLink(13));

        return nts::Tristate::Undefined;
    }

    nts::Tristate C4071::computeOr(nts::Tristate a, nts::Tristate b)
    {
        if (a == nts::Tristate::True || b == nts::Tristate::True)
            return nts::Tristate::True;
        if (a == nts::Tristate::False && b == nts::Tristate::False)
            return nts::Tristate::False;
        return nts::Tristate::Undefined;
    }
}
