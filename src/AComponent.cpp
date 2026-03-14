/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** AComponent.cpp
*/

#include "AComponent.hpp"

namespace nts {
    void AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
    {
        if (!isValidPin(pin)) {
            throw std::invalid_argument("Invalid pin " + std::to_string(pin) + 
                " on component '" + _name + "'");
        }
        // Store newest link at front; index 0 is always the most-recently connected.
        _links[pin].insert(_links[pin].begin(), std::make_pair(&other, otherPin));
    }

    nts::Tristate AComponent::getLink(std::size_t pin)
    {
        // Only block if THIS SPECIFIC PIN is already being computed (true cycle)
        if (_computingPins.count(pin))
            return nts::Tristate::Undefined;

        auto it = _links.find(pin);
        // If pin is not linked, return Undefined
        if (it == _links.end() || it->second.empty())
            return nts::Tristate::Undefined;

        // Get the linked component and its pin
        auto [linkedComponent, linkedPin] = it->second.front();
        
        // Guard against re-entrant calls on this component
        _computingPins.insert(pin);
        nts::Tristate result = linkedComponent->compute(linkedPin);
        _computingPins.erase(pin);
        return result;
    }

    // getLinkDirect: tries ALL links for this pin, oldest first.
    nts::Tristate AComponent::getLinkDirect(std::size_t pin)
    {
        auto it = _links.find(pin);
        if (it == _links.end() || it->second.empty())
            return nts::Tristate::Undefined;

        // Newest stored at front, so iterate in reverse for oldest-first
        for (auto rit = it->second.rbegin(); rit != it->second.rend(); ++rit) {
            auto [linkedComponent, linkedPin] = *rit;
            nts::Tristate result = linkedComponent->compute(linkedPin);
            if (result != nts::Tristate::Undefined)
                return result;
        }
        return nts::Tristate::Undefined;
    }

    bool AComponent::hasLink(std::size_t pin) const
    {
        auto it = _links.find(pin);
        return (it != _links.end() && !it->second.empty());
    }
}
