/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** InputComponent.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class InputComponent : public AComponent {
        public:
            InputComponent(void) :
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
                return pin == 1;
            };

            nts::Tristate _currentValue;
            nts::Tristate _nextValue;
            bool _hasPendingValue;
    };
}
