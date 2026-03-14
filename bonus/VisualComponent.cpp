/*
** EPITECH PROJECT, 2026
** VisualComponent.cpp
** File description:
** VisualComponent.cpp
*/

#include "GraphicalCircuit.hpp"
#include <cmath>
#include "AComponent.hpp"
#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"
#include "components/special/ClockComponent.hpp"
#include <iostream>

namespace bonus {

sf::Font VisualComponent::_font;
bool VisualComponent::_fontLoaded = false;

VisualComponent::VisualComponent(ComponentType type, const std::string& name, sf::Vector2f position)
    : _type(type), _name(name), _position(position), _selected(false), _logicComponent(nullptr)
{
    if (!_fontLoaded) {
        if (_font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") ||
            _font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf")) {
            _fontLoaded = true;
        }
    }
    _blinkClock.restart();
    _blinkState = true;
    updateShape();
    createPins();
}

void VisualComponent::updateShape()
{
    sf::Vector2f size(100.f, 60.f);
    
    _shape.setSize(size);
    _shape.setPosition(_position);
    sf::Color boxColor = getBoxColor();
    _shape.setFillColor(boxColor);
    _shape.setOutlineThickness(2.f);
    _shape.setOutlineColor(_selected ? sf::Color::Yellow : sf::Color::White);
    
    _label.setFont(_font);
    _label.setString(_name);
    _label.setCharacterSize(14);
    _label.setFillColor(sf::Color::White);
    
    sf::FloatRect textBounds = _label.getLocalBounds();
    _label.setPosition(
        _position.x + (size.x - textBounds.width) / 2.f,
        _position.y + (size.y - textBounds.height) / 2.f - 5.f
    );
}

void VisualComponent::draw(sf::RenderWindow& window)
{
    if (_type == ComponentType::OUTPUT) {
        _shape.setFillColor(getBoxColor());
    }
    window.draw(_shape);
    
    if (_fontLoaded) {
        window.draw(_label);
    }
    for (auto& pin : _pins) {
        sf::CircleShape pinCircle(5.f);
        pinCircle.setPosition(_position + pin.position - sf::Vector2f(5.f, 5.f));
        pinCircle.setFillColor(getColorForTristate(pin.value));
        pinCircle.setOutlineThickness(1.f);
        pinCircle.setOutlineColor(sf::Color::White);
        window.draw(pinCircle);
    }
}

bool VisualComponent::contains(sf::Vector2f point) const
{
    return _shape.getGlobalBounds().contains(point);
}

sf::Color VisualComponent::getColorForTristate(nts::Tristate value)
{
    switch (value) {
        case nts::Tristate::True:
            return sf::Color::Green;
        case nts::Tristate::False:
            return sf::Color::Red;
        case nts::Tristate::Undefined:
        default:
            return sf::Color(120, 120, 120);
    }
}

void Wire::draw(sf::RenderWindow& window)
{
    Pin* fromPin = nullptr;
    Pin* toPin = nullptr;
    
    for (auto& pin : _from->getPins()) {
        if (pin.number == _fromPin) {
            fromPin = &pin;
            break;
        }
    }
    for (auto& pin : _to->getPins()) {
        if (pin.number == _toPin) {
            toPin = &pin;
            break;
        }
    }
    if (!fromPin || !toPin)
        return;
    
    sf::Vector2f start = _from->getPosition() + fromPin->position;
    sf::Vector2f end = _to->getPosition() + toPin->position;
    sf::Color wireColor = getWireColor(fromPin->value);
    sf::Vector2f direction = end - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
    
    sf::RectangleShape line;
    line.setSize(sf::Vector2f(length, 3.f));
    line.setPosition(start);
    line.setRotation(angle);
    line.setFillColor(wireColor);
    line.setOrigin(0, 1.5f);
    window.draw(line);
}

sf::Color Wire::getWireColor(nts::Tristate value)
{
    switch (value) {
        case nts::Tristate::True:
            return sf::Color(0, 255, 0);      // vert vif
        case nts::Tristate::False:
            return sf::Color(255, 0, 0);      // rouge vif
        case nts::Tristate::Undefined:
        default:
            return sf::Color(150, 150, 150); // gris
    }
}

}