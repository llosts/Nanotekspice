/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4801.hpp
*/

#pragma once

#include <array>

#include "AComponent.hpp"

namespace nts {
    class C4801 : public AComponent {
        public:
            C4801(void) : _memory{}, _dataPins{} {
                _dataPins.fill(Tristate::Undefined);
            }

            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 24 && pin != 12 && pin != 19 && pin != 24);
            };

            int readAddress(void);

            std::array<unsigned char, 1024> _memory;
            std::array<nts::Tristate, 8> _dataPins; // cached output state per tick
    };
}
