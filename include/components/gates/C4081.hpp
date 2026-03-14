/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4081.hpp - Four AND gates
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C4081 : public AComponent {
        public:
            nts::Tristate compute(std::size_t pin) override;
        
        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 13 && pin != 7);
            };

            nts::Tristate computeAnd(nts::Tristate a, nts::Tristate b);
    };
}
