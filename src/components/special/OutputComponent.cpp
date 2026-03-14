/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** OutputComponent.cpp
*/

#include "components/special/OutputComponent.hpp"

namespace nts {
    nts::Tristate OutputComponent::compute(std::size_t pin) {
        (void)pin;
        return getLink(1);
    };
}
