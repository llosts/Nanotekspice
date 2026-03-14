/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C2716.hpp
*/

#pragma once

#include "AComponent.hpp"
#include <array>
#include <string>

namespace nts {
    class C2716 : public AComponent {
        public:
            C2716() : _memory{} { loadROM("./rom.bin"); }

            nts::Tristate compute(std::size_t pin) override;

        private:
            bool isValidPin(std::size_t pin) const override {
                return (pin >= 1 && pin <= 24 && pin != 12 && pin != 24);
            };

            void loadROM(const std::string& filename);
            int readAddress(void);

            std::array<unsigned char, 2048> _memory;
    };
}
