/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4069.cpp
*/

#include "components/gates/C4069.hpp"

namespace nts {
    nts::Tristate C4069::compute(std::size_t pin) {
        if (pin == 7 || pin == 14)
            return nts::Tristate::Undefined;

        if (pin == 2) return computeNot(getLink(1));
        if (pin == 4) return computeNot(getLink(3));
        if (pin == 6) return computeNot(getLink(5));
        if (pin == 8) return computeNot(getLink(9));
        if (pin == 10) return computeNot(getLink(11));
        if (pin == 12) return computeNot(getLink(13));

        return nts::Tristate::Undefined;
    }
    
    nts::Tristate C4069::computeNot(nts::Tristate input) {
        if (input == nts::Tristate::True)
            return nts::Tristate::False;
        if (input == nts::Tristate::False)
            return nts::Tristate::True;
        return nts::Tristate::Undefined;
    }
}
