/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** main.cpp
*/

#include <iostream>

#include "Parser.hpp"
#include "Circuit.hpp"
#include "Shell.hpp"
#include "Exceptions.hpp"

void printUsage(const char* program)
{
    std::cerr << "Usage: " << program << " <circuit_file.nts>" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printUsage(argv[0]);
        return 84;
    }
    
    try {
        nts::Circuit circuit;

        nts::Parser parser;
        parser.parseFile(argv[1], circuit);

        nts::Shell shell(circuit);
        shell.run();
        return 0;
     
    } catch (const nts::NanoTekSpiceException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 84;
    }
}
