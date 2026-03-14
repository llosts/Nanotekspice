/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** TrueComponent.cpp
*/

#include "components/special/TrueComponent.hpp"

namespace nts {
    nts::Tristate TrueComponent::compute(std::size_t pin) {
        (void)pin;
        return nts::Tristate::True;
    };
}
