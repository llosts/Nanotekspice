/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** OrComponent.cpp
*/

#include "components/elementary/OrComponent.hpp"

namespace nts {
    nts::Tristate OrComponent::compute(std::size_t pin) {
        if (pin != 3)
            return nts::Tristate::Undefined;

        nts::Tristate a = getLink(1);
        nts::Tristate b = getLink(2);

        if (a == nts::Tristate::True || b == nts::Tristate::True)
            return nts::Tristate::True;
        if (a == nts::Tristate::False && b == nts::Tristate::False)
            return nts::Tristate::False;
        return nts::Tristate::Undefined;
    };
}
