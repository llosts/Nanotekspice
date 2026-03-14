/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4071.hpp - Four OR gates
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C4071 : public AComponent {
        public:
            nts::Tristate compute(std::size_t pin) override;
        
        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 13 && pin != 7);
            };

            nts::Tristate computeOr(nts::Tristate a, nts::Tristate b);
    };
}
