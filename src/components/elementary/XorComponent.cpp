/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** XorComponent.cpp
*/

#include "components/elementary/XorComponent.hpp"

namespace nts {
    nts::Tristate XorComponent::compute(std::size_t pin) {
        if (pin != 3)
            return nts::Tristate::Undefined;

        nts::Tristate a = getLink(1);
        nts::Tristate b = getLink(2);

        if (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined)
            return nts::Tristate::Undefined;

        return (a != b) ? nts::Tristate::True : nts::Tristate::False; 
    };
}
