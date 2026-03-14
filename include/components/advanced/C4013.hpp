/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4013.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C4013 : public AComponent {
        public:
            C4013() : _q1(Tristate::Undefined), _q2(Tristate::Undefined),
                _lastClock1(Tristate::Undefined), _lastClock2(Tristate::Undefined) {}

            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 14 && pin != 7);
            };
            
            void handleFlipFlop(nts::Tristate clock, nts::Tristate lastClock, nts::Tristate data,
                nts::Tristate set, nts::Tristate reset, nts::Tristate& q);

            nts::Tristate _q1;  // Flip-flop 1 state
            nts::Tristate _q2;  // Flip-flop 2 state
            nts::Tristate _lastClock1;
            nts::Tristate _lastClock2;
    };
}
