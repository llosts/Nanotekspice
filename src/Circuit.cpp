/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** Circuit.cpp
*/

#include <iostream>
#include <algorithm>

#include "AComponent.hpp"
#include "Circuit.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"

namespace nts {
    void Circuit::addComponent(const std::string& name, std::unique_ptr<IComponent> component) {
        // Cast to AComponent to set the name
        AComponent* acomp = dynamic_cast<AComponent*>(component.get());
        if (acomp)
            acomp->setName(name);

        // Track inputs, clocks, and outputs for easy access
        InputComponent* input = dynamic_cast<InputComponent*>(component.get());
        if (input)
            _inputs[name] = input;

        ClockComponent* clock = dynamic_cast<ClockComponent*>(component.get());
        if (clock)
            _clocks[name] = clock;

        OutputComponent* output = dynamic_cast<OutputComponent*>(component.get());
        if (output)
            _outputs[name] = component.get();

        _components[name] = std::move(component);
    }

    IComponent* Circuit::getComponent(const std::string& name) {
        auto it = _components.find(name);
        if (it == _components.end())
            return nullptr;
        return it->second.get();
    }

    const IComponent* Circuit::getComponent(const std::string& name) const {
        auto it = _components.find(name);
        if (it == _components.end())
            return nullptr;
        return it->second.get();
    }

    void Circuit::setInputValue(const std::string& name, Tristate value) {
        auto inputIt = _inputs.find(name);
        if (inputIt != _inputs.end()) {
            inputIt->second->setValue(value);
            return;
        }

        auto clockIt = _clocks.find(name);
        if (clockIt != _clocks.end()) {
            clockIt->second->setValue(value);
            return;
        }

        throw ComponentException("'" + name + "' is not an input or clock");
    }

    std::vector<std::pair<std::string, Tristate>> Circuit::getInputs(void) const {
        std::vector<std::pair<std::string, Tristate>> inputs;

        // Add regular inputs
        for (const auto& [name, input] : _inputs)
            inputs.push_back({name, input->compute(1)});

        // Add clocks
        for (const auto& [name, clock] : _clocks)
            inputs.push_back({name, clock->compute(1)});

        // Sort by name
        std::sort(inputs.begin(), inputs.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });

        return inputs;
    }

    std::vector<std::pair<std::string, Tristate>> Circuit::getOutputs(void) const {
        std::vector<std::pair<std::string, Tristate>> outputs;

        for (const auto& [name, output] : _outputs)
            outputs.push_back({name, output->compute(1)});

        std::sort(outputs.begin(), outputs.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });

        return outputs;
    }

    void Circuit::simulate(void)
    {
        // Inputs and clocks must apply pending values first
        for (auto& [name, input] : _inputs)
            input->simulate(_tick);
        for (auto& [name, clock] : _clocks)
            clock->simulate(_tick);
        
        // Then simulate all chip components
        for (auto& [name, component] : _components) {
            if (_inputs.find(name) == _inputs.end() &&
                _clocks.find(name) == _clocks.end())
                component->simulate(_tick);
        }
        _tick++;
    }

    void Circuit::display(void) const
    {
        std::cout << "tick: " << _tick << std::endl;

        std::cout << "input(s):" << std::endl;
        for (const auto& [name, value] : getInputs()) {
            std::cout << "  " << name << ": " << value << std::endl;
        }

        std::cout << "output(s):" << std::endl;
        for (const auto& [name, value] : getOutputs()) {
            std::cout << "  " << name << ": " << value << std::endl;
        }
    }
}
