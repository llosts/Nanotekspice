/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** Shell.hpp
*/

#pragma once

#include <string>
#include <csignal>
#include <atomic>
#include <iostream>

#include "Circuit.hpp"

namespace nts {
    class Shell {
        public:
            explicit Shell(Circuit& circuit);
            ~Shell() { std::signal(SIGINT, SIG_DFL);};
            void run(void);

        private:
            Circuit& _circuit;
            bool _running;
            bool _looping;
            static std::atomic<bool> _interrupted;

            static void signalHandler(int signum);

            void handleCommand(const std::string& command);
            void cmdExit(void) { _running = false; _looping = false; };
            void cmdDisplay(void) { _circuit.display(); };
            void cmdSimulate(void) { _circuit.simulate(); };
            void cmdLoop(void);
            void cmdSetInput(const std::string& command);

            std::string readLine(void);
            void printPrompt(void) { std::cout << "> " << std::flush; };
    };
}
