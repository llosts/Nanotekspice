/*
** EPITECH PROJECT, 2026
** Createcomponent.cpp
** File description:
** Createcomponent
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
#include <algorithm>

namespace bonus {

ComponentPalette::ComponentPalette(sf::Vector2f position) : _position(position)
{
    _components = {
        {ComponentType::INPUT, "Input"},
        {ComponentType::OUTPUT, "Output"},
        {ComponentType::CLOCK, "Clock"},
        {ComponentType::AND, "AND"},
        {ComponentType::OR, "OR"},
        {ComponentType::XOR, "XOR"},
        {ComponentType::NOT, "NOT"}
    };
    _background.setSize(sf::Vector2f(150.f, static_cast<float>(_components.size() * 40 + 20)));
    _background.setPosition(_position);
    _background.setFillColor(sf::Color(30, 30, 30, 200));
    _background.setOutlineThickness(2.f);
    _background.setOutlineColor(sf::Color::White);
    _font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
}

void ComponentPalette::draw(sf::RenderWindow& window)
{
    window.draw(_background);
    
    for (size_t i = 0; i < _components.size(); i++) {
        sf::Text text;
        text.setFont(_font);
        text.setString(_components[i].second);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::White);
        text.setPosition(_position.x + 10.f, _position.y + 10.f + i * 40.f);
        window.draw(text);
    }
}

ComponentType ComponentPalette::getSelectedType(sf::Vector2f mousePos)
{
    if (!contains(mousePos))
        return ComponentType::INPUT;
    
    float relativeY = mousePos.y - _position.y - 10.f;
    size_t index = static_cast<size_t>(relativeY / 40.f);
    if (index < _components.size())
        return _components[index].first; 
    return ComponentType::INPUT;
}

bool ComponentPalette::contains(sf::Vector2f point) const
{
    return _background.getGlobalBounds().contains(point);
}

std::string GraphicalCircuit::createComponentName(ComponentType type)
{
    static int counter = 0;
    
    switch (type) {
        case ComponentType::INPUT: 
            return "input_" + std::to_string(counter++);
        case ComponentType::OUTPUT: 
            return "output_" + std::to_string(counter++);
        case ComponentType::CLOCK: 
            return "clock_" + std::to_string(counter++);
        case ComponentType::AND: 
            return "and_" + std::to_string(counter++);
        case ComponentType::OR: 
            return "or_" + std::to_string(counter++);
        case ComponentType::XOR: 
            return "xor_" + std::to_string(counter++);
        case ComponentType::NOT: 
            return "not_" + std::to_string(counter++);
        default: 
            return "comp_" + std::to_string(counter++);
    }
}

nts::IComponent* GraphicalCircuit::createLogicComponent(ComponentType type, const std::string& name)
{
    if (!_logicCircuit)
        return nullptr;
    
    std::string ntsType;
    switch (type) {
        case ComponentType::INPUT: 
            ntsType = "input"; 
            break;
        case ComponentType::OUTPUT: 
            ntsType = "output"; 
            break;
        case ComponentType::CLOCK: 
            ntsType = "clock"; 
            break;
        case ComponentType::AND: 
            ntsType = "and"; 
            break;
        case ComponentType::OR: 
            ntsType = "or"; 
            break;
        case ComponentType::XOR: 
            ntsType = "xor"; 
            break;
        case ComponentType::NOT: 
            ntsType = "not"; 
            break;
        default: 
            ntsType = "and"; 
            break;
    }
    nts::ComponentFactory factory;
    auto logic = factory.createComponent(ntsType);
    _logicCircuit->addComponent(name, std::move(logic));
    return _logicCircuit->getComponent(name);
}

void GraphicalCircuit::addComponentFromPalette(ComponentType type, sf::Vector2f position)
{
    std::string name = createComponentName(type);
    int index = _components.size();
    float x = 200.f + (index % 4) * 150.f;
    float y = 100.f + (index / 4) * 120.f; 
    (void)position;

    auto visual = std::make_unique<VisualComponent>(type, name, sf::Vector2f(x, y));
    nts::IComponent* logic = createLogicComponent(type, name);
    if (logic)
        visual->setLogicComponent(logic);
    _components.push_back(std::move(visual));
}

void GraphicalCircuit::addWire(VisualComponent* from, int fromPin, 
                               VisualComponent* to, int toPin)
{
    _wires.push_back(std::make_unique<Wire>(from, fromPin, to, toPin));
    
    if (from->getLogicComponent() && to->getLogicComponent()) {
        to->getLogicComponent()->setLink(toPin, *from->getLogicComponent(), fromPin);
    }
}

void GraphicalCircuit::deleteComponent(VisualComponent* component)
{
    if (!component)
        return;
    
    _wires.erase(
        std::remove_if(_wires.begin(), _wires.end(),
            [component](const std::unique_ptr<Wire>& wire) {
                return wire->getFrom() == component || wire->getTo() == component;
            }),
        _wires.end()
    );
    _components.erase(
        std::remove_if(_components.begin(), _components.end(),
            [component](const std::unique_ptr<VisualComponent>& comp) {
                return comp.get() == component;
            }),
        _components.end()
    );
}

}