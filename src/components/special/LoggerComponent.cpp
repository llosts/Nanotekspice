/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** LoggerComponent.cpp
*/

#include "components/special/LoggerComponent.hpp"

namespace nts {
    void LoggerComponent::simulate(std::size_t tick) {
        (void)tick;

        // Compute the byte first; bail if any data pin is undefined
        unsigned char byte = 0;
        for (int i = 0; i < 8; i++) {
            nts::Tristate bit = getLink(i + 1);
            if (bit == nts::Tristate::Undefined)
                return;
            if (bit == nts::Tristate::True)
                byte |= (1 << i);
        }

        nts::Tristate clock   = getLink(9);
        nts::Tristate inhibit = getLink(10);

        // only write when inhibit is explicitly False
        if (inhibit != nts::Tristate::False)
            return;

        if (clock == nts::Tristate::Undefined)
            return;

        if (clock == nts::Tristate::True) {
            // Write exactly once per HIGH phase - _hasPrint acts as a latch
            if (!_hasPrint) {
                std::ofstream file("./log.bin", std::ios::app | std::ios::binary);
                if (file.is_open()) {
                    file.put(static_cast<char>(byte));
                    file.close();
                }
                _hasPrint = true;
            }
        } else {
            // Clock LOW: re-arm for next rising edge
            _hasPrint = false;
        }
    }

    nts::Tristate LoggerComponent::compute(std::size_t pin) {
        (void)pin;
        return nts::Tristate::Undefined;
    }
}
