/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** FalseComponent.cpp
*/

#include "components/special/FalseComponent.hpp"

namespace nts {
    nts::Tristate FalseComponent::compute(std::size_t pin)
    {
        (void)pin;
        return nts::Tristate::False;
    }
}
