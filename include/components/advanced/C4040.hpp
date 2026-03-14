/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4040.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C4040 : public AComponent {
        public:
            C4040() : _count(0), _lastClock(Tristate::Undefined) {}

            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 16 && pin != 8 && pin != 16);
            };

            int _count;
            nts::Tristate _lastClock;
    };
}
