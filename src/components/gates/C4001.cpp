/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4001.cpp
*/

#include "components/gates/C4001.hpp"

namespace nts {
    void C4001::simulate(std::size_t tick) {
        (void)tick;
        for (int i = 0; i < 10; i++) {
            nts::Tristate new3 = computeGate(1, 2, 3);
            nts::Tristate new4 = computeGate(5, 6, 4);
            nts::Tristate new10 = computeGate(8, 9, 10);
            nts::Tristate new11 = computeGate(12, 13, 11);
            if (new3 == _outputs[3] && new4 == _outputs[4] &&
                    new10 == _outputs[10] && new11 == _outputs[11])
                break;
            _outputs[3]  = new3;
            _outputs[4]  = new4;
            _outputs[10] = new10;
            _outputs[11] = new11;
        }
    }

    nts::Tristate C4001::compute(std::size_t pin) {
        if (pin == 7 || pin == 14)
            return nts::Tristate::Undefined;
        auto it = _outputs.find(pin);
        if (it != _outputs.end())
            return it->second;
        return nts::Tristate::Undefined;
    }

    nts::Tristate C4001::computeGate(std::size_t pinA, std::size_t pinB, std::size_t outPin) {
        nts::Tristate a = getLink(pinA);
        nts::Tristate b = getLink(pinB);
        nts::Tristate result = computeNor(a, b);
        if (result == nts::Tristate::Undefined) {
            auto it = _outputs.find(outPin);
            if (it != _outputs.end())
                return it->second;
            return nts::Tristate::Undefined;
        }
        return result;
    }

    nts::Tristate C4001::computeNor(nts::Tristate a, nts::Tristate b) {
        if (a == nts::Tristate::True || b == nts::Tristate::True)
            return nts::Tristate::False;
        if (a == nts::Tristate::False && b == nts::Tristate::False)
            return nts::Tristate::True;
        return nts::Tristate::Undefined;
    }
}
