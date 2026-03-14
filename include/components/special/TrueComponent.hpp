/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** TrueComponent.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class TrueComponent : public AComponent {
        public:
            nts::Tristate compute(std::size_t pin) override;

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin == 1);
            };
    };
}
