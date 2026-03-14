/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** Parser.hpp
*/

#pragma once

#include <string>
#include <vector>

#include "Circuit.hpp"
#include "ComponentFactory.hpp"

namespace nts {
    struct LinkInfo {
        std::string component1;
        std::size_t pin1;
        std::string component2;
        std::size_t pin2;
    };

    class Parser {
        public:
            Parser() : _factory() {};

            void parseFile(const std::string& filename, Circuit& circuit);

        private:
            ComponentFactory _factory;

            enum class Section {
                None,
                Chipsets,
                Links
            };

            std::vector<std::string> readFile(const std::string& filename);
            std::string trim(const std::string& str);
            std::string removeComment(const std::string& line);
            bool isEmpty(const std::string& line) {
                return line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos;
            };

            void parseChipsetsSection(const std::vector<std::string>& lines, 
                                      std::size_t& index, Circuit& circuit);
            void parseLinksSection(const std::vector<std::string>& lines,
                                  std::size_t& index, Circuit& circuit);

            void parseChipsetLine(const std::string& line, Circuit& circuit);
            LinkInfo parseLinkLine(const std::string& line);

            void parseComponentPin(const std::string& str, std::string& component, std::size_t& pin);
    };
}
