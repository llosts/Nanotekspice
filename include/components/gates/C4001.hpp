/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4001.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C4001 : public AComponent {
        public:
            C4001() : _outputs({{3, Tristate::Undefined}, {4, Tristate::Undefined},
                {10, Tristate::Undefined}, {11, Tristate::Undefined}}) {}

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick) override;

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 13 && pin != 7);
            };

            nts::Tristate computeNor(nts::Tristate a, nts::Tristate b);
            nts::Tristate computeGate(std::size_t pinA, std::size_t pinB, std::size_t outPin);

            std::map<std::size_t, nts::Tristate> _outputs;
    };
}
