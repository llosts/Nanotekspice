/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** Exceptions.hpp
*/

#pragma once

#include <exception>
#include <string>

namespace nts {
    class NanoTekSpiceException : public std::exception {
        public:
            explicit NanoTekSpiceException(const std::string& message) 
                : _message(message) {}

            const char* what() const noexcept override {
                return _message.c_str();
            }

        private:
            std::string _message;
    };
    
    class ParsingException : public NanoTekSpiceException {
        public:
            explicit ParsingException(const std::string& message)
                : NanoTekSpiceException("Parsing error: " + message) {}
    };
    
    class ComponentException : public NanoTekSpiceException {
        public:
            explicit ComponentException(const std::string& message)
                : NanoTekSpiceException("Component error: " + message) {}
    };
    
    class CircuitException : public NanoTekSpiceException {
        public:
            explicit CircuitException(const std::string& message)
                : NanoTekSpiceException("Circuit error: " + message) {}
    };
    
    class PinException : public NanoTekSpiceException {
        public:
            explicit PinException(const std::string& message)
                : NanoTekSpiceException("Pin error: " + message) {}
    };

}
