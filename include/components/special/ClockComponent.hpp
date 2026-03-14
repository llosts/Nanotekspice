/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** ClockComponent.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class ClockComponent : public AComponent {
        public:
            ClockComponent() :
                _currentValue(nts::Tristate::Undefined),
                _nextValue(nts::Tristate::Undefined),
                _hasPendingValue(false) {}

            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;

            void setValue(nts::Tristate value) { 
                _nextValue = value;
                _hasPendingValue = true;
            }

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin == 1);
            };

            nts::Tristate _currentValue;  // Current value (what compute returns)
            nts::Tristate _nextValue;     // Pending value to apply
            bool _hasPendingValue;
    };
}
