/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4008.cpp
*/

#include "components/advanced/C4008.hpp"

namespace nts {
    nts::Tristate C4008::computeFullAdder(nts::Tristate a, nts::Tristate b,
            nts::Tristate carryIn, nts::Tristate& carryOut) {
        if (a == Tristate::Undefined || b == Tristate::Undefined || carryIn == Tristate::Undefined) {
            carryOut = Tristate::Undefined;
            return Tristate::Undefined;
        }

        int sum = ((a == Tristate::True) ? 1 : 0)
                + ((b == Tristate::True) ? 1 : 0)
                + ((carryIn == Tristate::True) ? 1 : 0);
        carryOut = (sum >= 2) ? Tristate::True : Tristate::False;

        return (sum % 2 == 1) ? Tristate::True : Tristate::False;
    }

    nts::Tristate C4008::compute(std::size_t pin) {
        if (pin == 8 || pin == 16)
            return nts::Tristate::Undefined;

        nts::Tristate carry;
        nts::Tristate cin = getLink(9);  // Carry input is pin 9

        if (pin == 10)  // S1 (bit 0)
            return computeFullAdder(getLink(7), getLink(6), cin, carry);

        if (pin == 11) {  // S2 (bit 1)
            computeFullAdder(getLink(7), getLink(6), cin, carry);
            return computeFullAdder(getLink(5), getLink(4), carry, carry);
        }

        if (pin == 12) {  // S3 (bit 2)
            computeFullAdder(getLink(7), getLink(6), cin, carry);
            computeFullAdder(getLink(5), getLink(4), carry, carry);
            return computeFullAdder(getLink(3), getLink(2), carry, carry);
        }

        if (pin == 13) {  // S4 (bit 3) — B4 is pin 15
            computeFullAdder(getLink(7), getLink(6), cin, carry);
            computeFullAdder(getLink(5), getLink(4), carry, carry);
            computeFullAdder(getLink(3), getLink(2), carry, carry);
            return computeFullAdder(getLink(1), getLink(15), carry, carry);
        }

        if (pin == 14) {  // Cout
            computeFullAdder(getLink(7), getLink(6), cin, carry);
            computeFullAdder(getLink(5), getLink(4), carry, carry);
            computeFullAdder(getLink(3), getLink(2), carry, carry);
            computeFullAdder(getLink(1), getLink(15), carry, carry);
            return carry;
        }

        return nts::Tristate::Undefined;
    }
}
