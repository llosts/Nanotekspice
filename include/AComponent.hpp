/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** AComponent.hpp
*/

#pragma once

#include "IComponent.hpp"

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <stdexcept>
#include <set>

namespace nts {
    class AComponent : public IComponent {
        protected:
            nts::Tristate getLink(std::size_t pin);
            nts::Tristate getLinkDirect(std::size_t pin);
            bool hasLink(std::size_t pin) const;

            std::string _name = "Unknown";
            std::set<std::size_t> _computingPins;

        public:
            virtual ~AComponent() = default;
        
            // Implements link management for all components
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
        
            // Default empty simulate (override in Clock, Input components)
            void simulate(std::size_t tick) override { (void)tick; };
        
            // Pure virtual - each component must define its logic
            virtual nts::Tristate compute(std::size_t pin) = 0;

            void setName(const std::string& name) { _name = name; }
            const std::string& getName() const { return _name; }
            const std::map<std::size_t, std::vector<std::pair<IComponent*, std::size_t>>>& getLinks() const {
                return _links;
            }

        private:
            virtual bool isValidPin(std::size_t pin) const = 0;
            // Each pin stores all connected components (newest first).
            std::map<std::size_t, std::vector<std::pair<IComponent*, std::size_t>>> _links;
        };
}
