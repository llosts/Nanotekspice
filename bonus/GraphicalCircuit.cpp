/*
** EPITECH PROJECT, 2026
** Graphic.cpp
** File description:
** Graphic.cpp
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

sf::Font GraphicalCircuit::_font;

GraphicalCircuit::GraphicalCircuit()
    : _window(sf::VideoMode(1400, 900), "NanoTekSpice - Circuit Editor"),
      _view(sf::FloatRect(0, 0, 1400, 900)),
      _palette(sf::Vector2f(10.f, 10.f)),
      _mode(EditorMode::SELECT),
      _selectedComponent(nullptr),
      _selectedPin(nullptr),
      _isDragging(false),
      _wireStart(nullptr),
      _wireStartPin(-1),
      _tick(0),
      _isSimulating(false),
      _zoomLevel(1.0f)
{
    _window.setFramerateLimit(60);
    _font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    _window.setView(_view);
    _logicCircuit = std::make_unique<nts::Circuit>();
}

GraphicalCircuit::~GraphicalCircuit()
{
}

void GraphicalCircuit::run()
{
    while (_window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GraphicalCircuit::simulate()
{
    std::cout << "Simulating tick " << _tick << "..." << std::endl;
    
    if (_logicCircuit) {
        syncInputsToLogic();
        _logicCircuit->simulate();
        updateVisualFromLogic();
    }
    _tick++;
}

void GraphicalCircuit::syncInputsToLogic()
{
    for (auto& comp : _components) {
        if (comp->getType() == ComponentType::INPUT || 
            comp->getType() == ComponentType::CLOCK) {
            
            nts::IComponent* logic = comp->getLogicComponent();
            if (!logic)
                continue;
            
            for (auto& pin : comp->getPins()) {
                if (pin.number == 1 && !pin.isInput) {
                    
                    if (comp->getType() == ComponentType::INPUT) {
                        nts::InputComponent* input = dynamic_cast<nts::InputComponent*>(logic);
                        if (input) {
                            input->setValue(pin.value);
                        }
                    } else if (comp->getType() == ComponentType::CLOCK) {
                        nts::ClockComponent* clock = dynamic_cast<nts::ClockComponent*>(logic);
                        if (clock) {
                            clock->setValue(pin.value);
                        }
                    }
                    break;
                }
            }
        }
    }
}

void GraphicalCircuit::reset()
{
    std::cout << "Resetting" << std::endl;
    _tick = 0;
}

void GraphicalCircuit::update()
{
}

void GraphicalCircuit::render()
{
    _window.clear(sf::Color(20, 20, 20));
    drawGrid();
    for (auto& wire : _wires) {
        wire->draw(_window);
    }
    for (auto& comp : _components) {
        comp->draw(_window);
    }
    sf::View uiView = _window.getDefaultView();
    _window.setView(uiView);
    _palette.draw(_window);
    drawUI();
    _window.setView(_view);
    _window.display();
}

void GraphicalCircuit::drawGrid()
{
    const float GRID_SIZE = 50.f;
    sf::Color gridColor(40, 40, 40);
    
    sf::FloatRect viewBounds(
        _view.getCenter().x - _view.getSize().x / 2,
        _view.getCenter().y - _view.getSize().y / 2,
        _view.getSize().x,
        _view.getSize().y
    );
    for (float x = 0; x < viewBounds.left + viewBounds.width; x += GRID_SIZE) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, viewBounds.top), gridColor),
            sf::Vertex(sf::Vector2f(x, viewBounds.top + viewBounds.height), gridColor)
        };
        _window.draw(line, 2, sf::Lines);
    }
    for (float y = 0; y < viewBounds.top + viewBounds.height; y += GRID_SIZE) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(viewBounds.left, y), gridColor),
            sf::Vertex(sf::Vector2f(viewBounds.left + viewBounds.width, y), gridColor)
        };
        _window.draw(line, 2, sf::Lines);
    }
}

void GraphicalCircuit::drawUI()
{
    sf::Text helpText;
    helpText.setFont(_font);
    helpText.setCharacterSize(14);
    helpText.setFillColor(sf::Color::White);
    
    std::string modeStr;
    switch (_mode) {
        case EditorMode::SELECT: 
            modeStr = "SELECT"; 
            break;
        case EditorMode::DRAW_WIRE: 
            modeStr = "DRAW WIRE"; 
            break;
        case EditorMode::DELETE: 
            modeStr = "DELETE"; 
            break;
    }
    int zoomPercent = (int)(100.0f / _zoomLevel);
    helpText.setString(
        "Mode: " + modeStr + "   Tick: " + std::to_string(_tick) + 
        "   Zoom: " + std::to_string(zoomPercent) + "%\n" + "\n" + "\n" +
        "Select = [S] | Wire = [W] | Delete = [D] | Simulate = [Space] | Reset = [R] | Zoom = [Scroll]"
    );
    helpText.setPosition(200.f, 10.f);
    _window.draw(helpText);
}

void GraphicalCircuit::updateVisualFromLogic()
{
    if (!_logicCircuit)
        return;
    for (auto& comp : _components) {
        comp->updatePinValues();
    }
}

void GraphicalCircuit::toggleInputValue(VisualComponent* comp)
{
    if (!comp)
        return;
    if (comp->getType() != ComponentType::INPUT && 
        comp->getType() != ComponentType::CLOCK) {
        return;
    }
    for (auto& pin : comp->getPins()) {
        if (pin.number == 1 && !pin.isInput) {
            if (pin.value == nts::Tristate::Undefined) {
                pin.value = nts::Tristate::False;
            } else if (pin.value == nts::Tristate::False) {
                pin.value = nts::Tristate::True;
            } else {
                pin.value = nts::Tristate::Undefined;
            }
            break;
        }
    }
}

}