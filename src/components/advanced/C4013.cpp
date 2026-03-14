/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** C4013.cpp
*/

#include "components/advanced/C4013.hpp"

namespace nts {
    void C4013::handleFlipFlop(nts::Tristate clock, nts::Tristate lastClock,
            nts::Tristate data, nts::Tristate set, nts::Tristate reset,
            nts::Tristate& q) {
        if (set == Tristate::True && reset == Tristate::True)
            q = Tristate::True; // Per datasheet truth table, Q=1, Q̄=1 when S=R=1
        else if (set == Tristate::True)
            q = Tristate::True;
        else if (reset == Tristate::True)
            q = Tristate::False;
        else if (clock == Tristate::True && lastClock != Tristate::True)
            q = data;
    }

    void C4013::simulate(std::size_t tick) {
        (void)tick;

        // Flip-flop 1: Clock on pin 3
        nts::Tristate clock1 = getLink(3);
        nts::Tristate data1 = getLink(5);
        nts::Tristate set1 = getLink(6);
        nts::Tristate reset1 = getLink(4);

        // Flip-flop 2: Clock on pin 11
        nts::Tristate clock2 = getLink(11);
        nts::Tristate data2 = getLink(9);
        nts::Tristate set2 = getLink(8);
        nts::Tristate reset2 = getLink(10);

        handleFlipFlop(clock1, _lastClock1, data1, set1, reset1, _q1);
        _lastClock1 = clock1;

        handleFlipFlop(clock2, _lastClock2, data2, set2, reset2, _q2);
        _lastClock2 = clock2;
    }

    nts::Tristate C4013::compute(std::size_t pin) {
        if (pin == 7 || pin == 14)
            return Tristate::Undefined;

        // Async helper: resolve Q value with real-time set/reset override
        auto resolveQ = [&](nts::Tristate q, nts::Tristate set, nts::Tristate reset) -> nts::Tristate {
            if (set == Tristate::True && reset == Tristate::True)
                return Tristate::True;
            if (set == Tristate::True)
                return Tristate::True;
            if (reset == Tristate::True)
                return Tristate::False;
            return q;
        };

        // Flip-flop 1
        if (pin == 1 || pin == 2) {
            nts::Tristate set1 = getLink(6);
            nts::Tristate reset1 = getLink(4);
            nts::Tristate q1 = resolveQ(_q1, set1, reset1);
            if (pin == 1)
                return q1;
            if (set1 == Tristate::True && reset1 == Tristate::True)
                return Tristate::True; // Per datasheet when S=R=1 both Q and QB are HIGH
            return (q1 == Tristate::True) ? Tristate::False :
                   (q1 == Tristate::False) ? Tristate::True : Tristate::Undefined;
        }

        // Flip-flop 2
        if (pin == 13 || pin == 12) {
            nts::Tristate set2 = getLink(8);
            nts::Tristate reset2 = getLink(10);
            nts::Tristate q2 = resolveQ(_q2, set2, reset2);
            if (pin == 13)
                return q2;
            if (set2 == Tristate::True && reset2 == Tristate::True)
                return Tristate::True; // Per datasheet when S=R=1 both Q and QB are HIGH
            return (q2 == Tristate::True) ? Tristate::False :
                   (q2 == Tristate::False) ? Tristate::True : Tristate::Undefined;
        }

        return Tristate::Undefined;
    }
}
