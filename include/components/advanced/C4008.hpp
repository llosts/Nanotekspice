/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4008.hpp
*/

#pragma once

#include <vector>

#include "AComponent.hpp"

namespace nts {
    class C4008 : public AComponent {
        public:
            nts::Tristate compute(std::size_t pin) override;

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 16 && pin != 8);
            };

            nts::Tristate computeFullAdder(nts::Tristate a, nts::Tristate b,
                nts::Tristate carryIn, nts::Tristate& carryOut);
            nts::Tristate computeBit(const std::vector<std::size_t>& pins);
            nts::Tristate computeBitWithCarry(const std::vector<std::size_t>& pins);
            nts::Tristate computeBitWithCarries(const std::vector<std::size_t>& pins);
            nts::Tristate computeCarryOut(void);
    };
}
