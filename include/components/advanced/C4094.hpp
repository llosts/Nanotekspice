/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4094.hpp
*/

#pragma once

#include <array>

#include "AComponent.hpp"

namespace nts {
    class C4094 : public AComponent {
        public:
            C4094() : _lastClock(Tristate::Undefined), _qe(Tristate::Undefined) { _register.fill(Tristate::Undefined);}

            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 16 && pin != 8);
            };

            std::array<nts::Tristate, 8> _register;
            nts::Tristate _lastClock;
            nts::Tristate _qe; // Captured Q'S on falling edge (NOT inverted)
    };
}
