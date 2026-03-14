/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** Shell.cpp
*/

#include <sstream>
#include <cstdlib>

#include "Exceptions.hpp"
#include "Shell.hpp"
#include "Utils.hpp"

namespace nts {
    std::atomic<bool> Shell::_interrupted{false};

    void Shell::signalHandler(int signum) {
        (void)signum;
        _interrupted = true;
    }

    Shell::Shell(Circuit& circuit) 
        : _circuit(circuit), _running(true), _looping(false) {
        std::signal(SIGINT, signalHandler);
    }

    void Shell::run(void) {
        _looping = false;

        while (_running) {
            if (!_looping)
                printPrompt();

            std::string command = readLine();

            if (std::cin.eof()) {
                _running = false;
                break;
            }

            try {
                handleCommand(command);
            } catch (const NanoTekSpiceException& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    void Shell::handleCommand(const std::string& command) {
        if (command.empty())
            return;

        if (command == "exit")
            cmdExit();
        else if (command == "display")
            cmdDisplay();
        else if (command == "simulate")
            cmdSimulate();
        else if (command == "loop")
            cmdLoop();
        else if (command.find('=') != std::string::npos)
            cmdSetInput(command);
        else
            std::cerr << "Unknown command: " << command << std::endl;
    }

    void Shell::cmdLoop(void) {
        _looping = true;
        _interrupted = false;

        while (_looping && _running && !_interrupted) {
            _circuit.simulate();
            _circuit.display();
        }

        if (_interrupted) {
            std::cout << std::endl;
            _interrupted = false;
            _looping = false;
        }
    }

    void Shell::cmdSetInput(const std::string& command)
    {
        size_t pos = command.find('=');
        if (pos == std::string::npos) {
            throw ParsingException("Invalid input command: " + command);
        }

        std::string name = command.substr(0, pos);
        std::string valueStr = command.substr(pos + 1);

        name = nts::trim(name);
        valueStr = nts::trim(valueStr);

        Tristate value;
        if (valueStr == "0")
            value = Tristate::False;
        else if (valueStr == "1")
            value = Tristate::True;
        else if (valueStr == "U")
            value = Tristate::Undefined;
        else
            throw ParsingException("Invalid value '" + valueStr + "' (must be 0, 1, or U)");

        _circuit.setInputValue(name, value);
    }

    std::string Shell::readLine(void) {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }
}
