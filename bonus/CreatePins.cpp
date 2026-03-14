/*
** EPITECH PROJECT, 2026
** CreatePins.cpp
** File description:
** CreatePins.cpp
*/

#include "GraphicalCircuit.hpp"
#include "Circuit.hpp"
#include "ComponentFactory.hpp"
#include "AComponent.hpp"
#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"
#include "components/special/ClockComponent.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

namespace bonus {

void VisualComponent::createPins()
{
    _pins.clear();
    sf::Vector2f size = _shape.getSize();
    
    switch (_type) {
        case ComponentType::INPUT:
        case ComponentType::CLOCK:
            _pins.push_back(Pin(sf::Vector2f(size.x, size.y / 2.f), 1, false));
            _pins.back().value = nts::Tristate::False;
            break;
        case ComponentType::OUTPUT:
            _pins.push_back(Pin(sf::Vector2f(0.f, size.y / 2.f), 1, true));
            break;
        case ComponentType::NOT:
            _pins.push_back(Pin(sf::Vector2f(0.f, size.y / 2.f), 1, true));
            _pins.push_back(Pin(sf::Vector2f(size.x, size.y / 2.f), 2, false));
            break;  
        case ComponentType::AND:
        case ComponentType::OR:
        case ComponentType::XOR:
            _pins.push_back(Pin(sf::Vector2f(0.f, size.y / 3.f), 1, true));
            _pins.push_back(Pin(sf::Vector2f(0.f, 2.f * size.y / 3.f), 2, true));
            _pins.push_back(Pin(sf::Vector2f(size.x, size.y / 2.f), 3, false));
            break;    
        default:
            break;
    }
}

void VisualComponent::updatePinValues()
{
    if (!_logicComponent) {
        return;
    }  
    for (auto& pin : _pins) {
        pin.value = _logicComponent->compute(pin.number);
    }
    if (_type == ComponentType::OUTPUT) {
        updateShape();
    }
}

sf::Color VisualComponent::getBoxColor()
{
    if (_type != ComponentType::OUTPUT) {
        return sf::Color(50, 50, 50);
    }
    if (_pins.empty()) {
        return sf::Color(50, 50, 50);
    }
    nts::Tristate value = _pins[0].value;
    
    if (value == nts::Tristate::True) {
        if (_blinkClock.getElapsedTime().asMilliseconds() > 500) {
            _blinkState = !_blinkState;
            _blinkClock.restart();
        }
        if (_blinkState) {
            return sf::Color(0, 200, 0);      
        } else {
            return sf::Color(0, 100, 0);      
        }
    }
    else if (value == nts::Tristate::False) {
        return sf::Color(150, 0, 0);          
    }
    else {
        return sf::Color(80, 80, 80);       
    }
}

Pin* VisualComponent::getPinAt(sf::Vector2f point)
{
    const float PIN_RADIUS = 10.f;
    
    for (auto& pin : _pins) {
        sf::Vector2f pinPos = _position + pin.position;
        float dx = point.x - pinPos.x;
        float dy = point.y - pinPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);
        if (distance <= PIN_RADIUS) {
            return &pin;
        }
    }
    
    return nullptr;
}

}
