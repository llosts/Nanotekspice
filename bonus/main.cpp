/*
** EPITECH PROJECT, 2026
** main.cpp
** File description:
** main.cpp
*/

#include "GraphicalCircuit.hpp"
#include <cmath>
#include "AComponent.hpp"
#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"
#include "components/special/ClockComponent.hpp"
#include <iostream>

void printUsage(const char* program)
{
    std::cout << "NanoTekSpice - Graphical Circuit Editor" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  " << program << "                  # Start empty editor" << std::endl;
    std::cout << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  [S] - Select mode (drag components)" << std::endl;
    std::cout << "  [W] - Wire mode (click pins to connect)" << std::endl;
    std::cout << "  [D] - Delete mode (click to delete)" << std::endl;
    std::cout << "  [Space] - Simulate one tick" << std::endl;
    std::cout << "  [R] - Reset circuit" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    try {
        if (argc == 2) {
            std::string arg = argv[1];
            if (arg == "-h") {
                printUsage(argv[0]);
                return 0;
            } else {
                std::cout << "Unknown argument: " << arg << std::endl;
                return 84;
            }
        }
        std::cout << "Starting empty editor..." << std::endl;
        bonus::GraphicalCircuit editor;
        editor.run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
}