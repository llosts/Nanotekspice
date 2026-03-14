#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <vector>
#include <string>
#include "IComponent.hpp"

namespace nts {
    class IComponent;
    enum Tristate;
}

namespace bonus {
    
    enum class ComponentType {
        INPUT,
        OUTPUT,
        CLOCK,
        AND,
        OR,
        XOR,
        NOT
    };

    struct Pin {
        sf::Vector2f position;
        int number;
        bool isInput;
        nts::Tristate value;
        
        Pin(sf::Vector2f pos, int num, bool input) 
            : position(pos), number(num), isInput(input), value(static_cast<nts::Tristate>(-1)) {}
    };

    class VisualComponent {
    public:
        VisualComponent(ComponentType type, const std::string& name, sf::Vector2f position);
        
        void draw(sf::RenderWindow& window);
        void setPosition(sf::Vector2f pos) { _position = pos; updateShape(); }
        sf::Vector2f getPosition() const { return _position; }
        
        bool contains(sf::Vector2f point) const;
        Pin* getPinAt(sf::Vector2f point);
        
        void setSelected(bool selected) { _selected = selected; updateShape(); }
        bool isSelected() const { return _selected; }
        
        void setLogicComponent(nts::IComponent* component) { _logicComponent = component; }
        nts::IComponent* getLogicComponent() const { return _logicComponent; }
        
        ComponentType getType() const { return _type; }
        const std::string& getName() const { return _name; }
        const std::vector<Pin>& getPins() const { return _pins; }
        std::vector<Pin>& getPins() { return _pins; }
        
        void updatePinValues();
        
    private:
        void updateShape();
        void createPins();
        sf::Color getColorForTristate(nts::Tristate value);
        sf::Color getBoxColor();
        
        ComponentType _type;
        std::string _name;
        sf::Vector2f _position;
        sf::RectangleShape _shape;
        sf::Text _label;
        std::vector<Pin> _pins;
        bool _selected;
        
        nts::IComponent* _logicComponent;
        
        sf::Clock _blinkClock;
        bool _blinkState;
        static sf::Font _font;
        static bool _fontLoaded;
    };

    class Wire {
    public:
        Wire(VisualComponent* from, int fromPin, VisualComponent* to, int toPin)
            : _from(from), _fromPin(fromPin), _to(to), _toPin(toPin) {}
        
        void draw(sf::RenderWindow& window);  
        VisualComponent* getFrom() const { return _from; }
        int getFromPin() const { return _fromPin; }
        VisualComponent* getTo() const { return _to; }
        int getToPin() const { return _toPin; }
        
    private:
        sf::Color getWireColor(nts::Tristate value);
        VisualComponent* _from;
        int _fromPin;
        VisualComponent* _to;
        int _toPin;
    };
}
