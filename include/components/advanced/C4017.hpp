/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4017.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C4017 : public AComponent {
        public:
            C4017() : _counter(0),  _lastCP0(Tristate::Undefined), _lastCP1(Tristate::Undefined) {}

            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 16 && pin != 8);
            };

            int _counter;  // 0-9
            nts::Tristate _lastCP0;
            nts::Tristate _lastCP1;
    };
}
