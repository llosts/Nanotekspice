/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** InputComponent.cpp
*/

#include "components/special/InputComponent.hpp"

namespace nts {
    void InputComponent::simulate(std::size_t tick) {
        (void)tick;
        if (_hasPendingValue) {
            _currentValue = _nextValue;
            _hasPendingValue = false;
        }
    }

    nts::Tristate InputComponent::compute(std::size_t pin) {
        (void)pin;
        return _currentValue;
    };
}
