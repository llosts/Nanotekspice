/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4514.hpp - 4-bit decoder
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C4514 : public AComponent {
        public:
            C4514() {}

            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 24 && pin != 12);
            };
            bool isOutputPin(std::size_t pin);
    };
}
