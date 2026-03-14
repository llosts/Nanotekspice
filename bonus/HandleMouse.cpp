/*
** EPITECH PROJECT, 2026
** HandleMouse.cpp
** File description:
** HandleMouse.cpp
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

void GraphicalCircuit::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = _window.mapPixelToCoords(
                sf::Mouse::getPosition(_window)
            );
            handleMousePressed(mousePos, event.mouseButton.button);
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            sf::Vector2f mousePos = _window.mapPixelToCoords(
                sf::Mouse::getPosition(_window)
            );
            handleMouseReleased(mousePos);
        }
        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2f mousePos = _window.mapPixelToCoords(
                sf::Mouse::getPosition(_window)
            );
            handleMouseMoved(mousePos);
        }
        if (event.type == sf::Event::KeyPressed) {
            handleKeyPressed(event.key.code);
        }
        if (event.type == sf::Event::MouseWheelScrolled) {
            handleZoom(event.mouseWheelScroll.delta);
        }
    }
}

void GraphicalCircuit::handleZoom(float delta)
{
    if (delta > 0) {
        _zoomLevel *= 0.9f;
    } else {
        _zoomLevel *= 1.1f;
    }
    if (_zoomLevel < 0.5f) _zoomLevel = 0.5f;
    if (_zoomLevel > 3.0f) _zoomLevel = 3.0f;
    _view.setSize(1400 * _zoomLevel, 900 * _zoomLevel);
    _window.setView(_view);
}

void GraphicalCircuit::handleKeyPressed(sf::Keyboard::Key key)
{
    switch (key) {
        case sf::Keyboard::S:
            _mode = EditorMode::SELECT;
            std::cout << "Mode: SELECT" << std::endl;
            break;
        case sf::Keyboard::W:
            _mode = EditorMode::DRAW_WIRE;
            _wireStart = nullptr;
            std::cout << "Mode: DRAW WIRE" << std::endl;
            break;
        case sf::Keyboard::D:
            _mode = EditorMode::DELETE;
            std::cout << "Mode: DELETE" << std::endl;
            break;
        case sf::Keyboard::Space:
            simulate();
            break;
        case sf::Keyboard::R:
            reset();
            break;
        default:
            break;
    }
}

void GraphicalCircuit::handleMousePressed(sf::Vector2f mousePos, sf::Mouse::Button button)
{
    if (button != sf::Mouse::Left)
        return;
    
    if (_palette.contains(mousePos)) {
        ComponentType type = _palette.getSelectedType(mousePos);
        addComponentFromPalette(type, sf::Vector2f(200.f, 200.f + _components.size() * 100.f));
        return;
    }
    
    switch (_mode) {
        case EditorMode::SELECT: {
            _selectedComponent = nullptr;
            for (auto& comp : _components) {
                if (comp->contains(mousePos)) {
                    _selectedComponent = comp.get();
                    comp->setSelected(true);
                    _isDragging = true;
                    _dragOffset = comp->getPosition() - mousePos;
                    
                    if (comp->getType() == ComponentType::INPUT || 
                        comp->getType() == ComponentType::CLOCK) {
                        toggleInputValue(comp.get());
                    }
                } else {
                    comp->setSelected(false);
                }
            }
            break;
        }
        
        case EditorMode::DRAW_WIRE: {
            for (auto& comp : _components) {
                Pin* pin = comp->getPinAt(mousePos);
                if (pin) {
                    if (!_wireStart) {
                        _wireStart = comp.get();
                        _wireStartPin = pin->number;
                    } else {
                        addWire(_wireStart, _wireStartPin, comp.get(), pin->number);
                        _wireStart = nullptr;
                    }
                    break;
                }
            }
            break;
        }
        case EditorMode::DELETE: {
            for (auto it = _components.begin(); it != _components.end(); ) {
                if ((*it)->contains(mousePos)) {
                    std::cout << "Deleted component: " << (*it)->getName() << std::endl;
                    deleteComponent((*it).get());
                    return;
                } else {
                    ++it;
                }
            }
            break;
        }
    }
}

void GraphicalCircuit::handleMouseReleased(sf::Vector2f mousePos)
{
    (void)mousePos;
    _isDragging = false;
}

void GraphicalCircuit::handleMouseMoved(sf::Vector2f mousePos)
{
    if (_isDragging && _selectedComponent) {
        _selectedComponent->setPosition(mousePos + _dragOffset);
    }
}
    
}
