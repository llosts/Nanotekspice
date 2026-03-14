/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** NotComponent.cpp
*/

#include "components/elementary/NotComponent.hpp"

namespace nts {
    nts::Tristate NotComponent::compute(std::size_t pin) {
        if (pin != 2)
            return nts::Tristate::Undefined;

        nts::Tristate input = getLink(1);

        if (input == nts::Tristate::Undefined)
            return nts::Tristate::Undefined;
        return (input == nts::Tristate::True) ? nts::Tristate::False : nts::Tristate::True;
    };
}
