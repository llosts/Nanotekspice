/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** LoggerComponent.hpp
*/

#pragma once

#include <fstream>

#include "AComponent.hpp"

namespace nts {
    class LoggerComponent : public AComponent {
        public:
            LoggerComponent(void) : _hasPrint(false) {};

            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 10);
            };

            bool _hasPrint; // true while clock is HIGH and we've already logged for this phase, to prevent multiple writes
    };
}
