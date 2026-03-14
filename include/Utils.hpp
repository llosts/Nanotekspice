/*
** EPITECH PROJECT, 2025
** G-OOP-400 [WSL: Ubuntu-24.04]
** File description:
** Utils.hpp
*/

#pragma once

#include <iostream>

#include "IComponent.hpp"

namespace nts {
    inline std::ostream& operator<<(std::ostream &s, nts::Tristate v) {
        switch (v) {
            case nts::Tristate::True:
                s << "1";
                break;
            case nts::Tristate::False:
                s << "0";
                break;
            case nts::Tristate::Undefined:
                s << "U";
                break;
        }
        return s;
    }

    inline std::string trim(const std::string& str) {
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start))
            start++;

        auto end = str.end();
        do {
            end--;
        } while (std::distance(start, end) > 0 && std::isspace(*end));

        return std::string(start, end + 1);
    }
}
