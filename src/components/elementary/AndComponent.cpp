/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** AndComponent.cpp
*/

#include "components/elementary/AndComponent.hpp"

namespace nts {
    nts::Tristate AndComponent::compute(std::size_t pin) {
        if (pin != 3)
            return nts::Tristate::Undefined;

        nts::Tristate a = getLink(1);
        nts::Tristate b = getLink(2);

        if (a == nts::Tristate::False || b == nts::Tristate::False)
            return nts::Tristate::False;
        if (a == nts::Tristate::True && b == nts::Tristate::True)
            return nts::Tristate::True;
        return nts::Tristate::Undefined;
    };
}
