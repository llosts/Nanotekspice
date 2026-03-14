/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** ClockComponent.cpp
*/

#include "components/special/ClockComponent.hpp"

namespace nts {
    void ClockComponent::simulate(std::size_t tick)
    {
        (void)tick;
        if (_hasPendingValue) {
            _currentValue = _nextValue;
            _hasPendingValue = false;
            return;
        }

        if (_currentValue != nts::Tristate::Undefined) {
            _currentValue = (_currentValue == nts::Tristate::True) 
                ? nts::Tristate::False 
                : nts::Tristate::True;
    }
    }

    nts::Tristate ClockComponent::compute(std::size_t pin) {
        (void)pin;
        return _currentValue;
    }
}
