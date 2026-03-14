/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** Parser.cpp
*/

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "Parser.hpp"
#include "Utils.hpp"
#include "Exceptions.hpp"

namespace nts {
    void Parser::parseFile(const std::string& filename, Circuit& circuit) {
        auto lines = readFile(filename);
        std::size_t index = 0;

        while (index < lines.size()) {
            std::string line = removeComment(lines[index]);
            line = nts::trim(line);

            if (isEmpty(line)) {
                index++;
                continue;
            }
            if (line == ".chipsets:") {
                index++;
                parseChipsetsSection(lines, index, circuit);
            } else if (line == ".links:") {
                index++;
                parseLinksSection(lines, index, circuit);
            } else {
                index++;
            }
        }

        if (circuit.getComponentCount() == 0)
            throw CircuitException("No chipsets in the circuit");
    }

    std::vector<std::string> Parser::readFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open())
            throw ParsingException("Cannot open file '" + filename + "'");

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line))
            lines.push_back(line);

        return lines;
    }

    std::string Parser::removeComment(const std::string& line) {
        size_t pos = line.find('#');
        if (pos != std::string::npos)
            return line.substr(0, pos);
        return line;
    }

    void Parser::parseChipsetsSection(const std::vector<std::string>& lines,
            std::size_t& index, Circuit& circuit) {
        while (index < lines.size()) {
            std::string line = removeComment(lines[index]);
            line = nts::trim(line);

            if (isEmpty(line)) {
                index++;
                continue;
            }
            if (line[0] == '.')
                return;
            parseChipsetLine(line, circuit);
            index++;
        }
    }

    void Parser::parseChipsetLine(const std::string& line, Circuit& circuit) {
        std::istringstream iss(line);
        std::string type, name;

        if (!(iss >> type >> name))
            throw ParsingException("Invalid chipset line: " + line);

        if (circuit.hasComponent(name))
            throw ComponentException("Duplicate component name '" + name + "'");

        auto component = _factory.createComponent(type);
        circuit.addComponent(name, std::move(component));
    }

    void Parser::parseLinksSection(const std::vector<std::string>& lines,
            std::size_t& index, Circuit& circuit) {
        while (index < lines.size()) {
            std::string line = removeComment(lines[index]);
            line = nts::trim(line);

            if (isEmpty(line)) {
                index++;
                continue;
            }
            if (line[0] == '.')
                return;
            LinkInfo link = parseLinkLine(line);

            IComponent* comp1 = circuit.getComponent(link.component1);
            IComponent* comp2 = circuit.getComponent(link.component2);
            if (!comp1)
                throw ComponentException("Unknown component name '" + link.component1 + "'");
            if (!comp2)
                throw ComponentException("Unknown component name '" + link.component2 + "'");

            comp1->setLink(link.pin1, *comp2, link.pin2);
            comp2->setLink(link.pin2, *comp1, link.pin1);
            index++;
        }
    }

    LinkInfo Parser::parseLinkLine(const std::string& line) {
        std::istringstream iss(line);
        std::string comp1Str, comp2Str;

        if (!(iss >> comp1Str >> comp2Str))
            throw ParsingException("Invalid link line: " + line);

        LinkInfo link;
        parseComponentPin(comp1Str, link.component1, link.pin1);
        parseComponentPin(comp2Str, link.component2, link.pin2);

        return link;
    }

    void Parser::parseComponentPin(const std::string& str, std::string& component, std::size_t& pin) {
        size_t colonPos = str.find(':');
        if (colonPos == std::string::npos)
            throw ParsingException("Invalid component:pin format: " + str);

        component = str.substr(0, colonPos);
        std::string pinStr = str.substr(colonPos + 1);

        try {
            pin = std::stoull(pinStr);
        } catch (...) {
            throw ParsingException("Invalid pin number: " + pinStr);
        }
    }
}
