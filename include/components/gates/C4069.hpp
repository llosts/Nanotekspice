/*
** EPITECH PROJECT, 2025
** G-OOP-400
** File description:
** C4069.hpp - Six NOT gates
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class C4069 : public AComponent {
        public:
            nts::Tristate compute(std::size_t pin) override;
        
        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 13 && pin != 7);
            };

            nts::Tristate computeNot(nts::Tristate input);
    };
}
