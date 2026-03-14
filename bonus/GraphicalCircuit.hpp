/*
** EPITECH PROJECT, 2026
** Graphic.hpp
** File description:
** Graphic.hpp
*/

#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>
#include "VisualComponent.hpp"

namespace nts {
    class Circuit;
    class IComponent;
}

namespace bonus {

    enum class EditorMode {
        SELECT,
        DRAW_WIRE,
        DELETE
    };

    class ComponentPalette {
    public:
        ComponentPalette(sf::Vector2f position);
        
        void draw(sf::RenderWindow& window);
        ComponentType getSelectedType(sf::Vector2f mousePos);
        bool contains(sf::Vector2f point) const;
        
    private:
        sf::Vector2f _position;
        std::vector<std::pair<ComponentType, std::string>> _components;
        sf::RectangleShape _background;
        sf::Font _font;
    };

    class GraphicalCircuit {
    public:
        GraphicalCircuit();
        ~GraphicalCircuit();
        
        void run();
        
    private:
        void processEvents();
        void update();
        void render();
        
        void handleMousePressed(sf::Vector2f mousePos, sf::Mouse::Button button);
        void handleMouseReleased(sf::Vector2f mousePos);
        void handleMouseMoved(sf::Vector2f mousePos);
        void handleKeyPressed(sf::Keyboard::Key key);
        void handleZoom(float delta);
        
        std::string createComponentName(ComponentType type);
        nts::IComponent* createLogicComponent(ComponentType type, const std::string& name);
        
        void addComponentFromPalette(ComponentType type, sf::Vector2f position);
        void deleteComponent(VisualComponent* component);
        void addWire(VisualComponent* from, int fromPin, VisualComponent* to, int toPin);
        void toggleInputValue(VisualComponent* comp);
        void syncInputsToLogic(); 
        void updateVisualFromLogic();
        void simulate();
        void reset();
        void drawGrid();
        void drawUI();
        
        sf::RenderWindow _window;
        sf::View _view;
        std::vector<std::unique_ptr<VisualComponent>> _components;
        std::vector<std::unique_ptr<Wire>> _wires;
        
        ComponentPalette _palette;
        EditorMode _mode;
        
        VisualComponent* _selectedComponent;
        Pin* _selectedPin;
        bool _isDragging;
        sf::Vector2f _dragOffset;
        
        VisualComponent* _wireStart;
        int _wireStartPin;
        
        std::unique_ptr<nts::Circuit> _logicCircuit;
        
        size_t _tick;
        bool _isSimulating;
        float _zoomLevel;
        
        static sf::Font _font;
    };

}
#endif
