/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** Circuit.hpp
*/

#pragma once

#include <memory>
#include <map>
#include <string>
#include <vector>

#include "IComponent.hpp"
#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"
#include "components/special/ClockComponent.hpp"


namespace nts {
    class Circuit {
        public:
            void addComponent(const std::string& name, std::unique_ptr<IComponent> component);
            IComponent* getComponent(const std::string& name);
            const IComponent* getComponent(const std::string& name) const;
            bool hasComponent(const std::string& name) const {
                return _components.find(name) != _components.end();
            };
            std::size_t getComponentCount(void) const {
                return _components.size();
            };

            void setInputValue(const std::string& name, Tristate value);
            std::vector<std::pair<std::string, Tristate>> getInputs() const;
            std::vector<std::pair<std::string, Tristate>> getOutputs() const;

            void simulate(void);
            void display(void) const;
            std::size_t getTick(void) const { return _tick; }
            const std::map<std::string, std::unique_ptr<IComponent>>& getComponents() const {
                return _components;
            }


        private:
            std::map<std::string, std::unique_ptr<IComponent>> _components;
            std::map<std::string, InputComponent*> _inputs;
            std::map<std::string, ClockComponent*> _clocks;
            std::map<std::string, IComponent*> _outputs;
            std::size_t _tick = 0;
    };
}
