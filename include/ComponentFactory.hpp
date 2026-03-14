/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-27
** File description:
** ComponentFactory.hpp
*/

#pragma once

#include <memory>
#include <string>
#include <functional>
#include <map>

#include "IComponent.hpp"

namespace nts {
    class ComponentFactory {
        public:
            ComponentFactory() { registerComponents(); }

            // Main factory method
            std::unique_ptr<IComponent> createComponent(const std::string& type);

            bool hasComponent(const std::string& type) const {
                return _creators.find(type) != _creators.end();
            }

        private:
            // Map of component type -> creation function
            std::map<std::string, std::function<std::unique_ptr<IComponent>()>> _creators;

            void registerComponents();
            void registerSpecialComponents();
            void registerElementaryComponents();
            void registerGateComponents();
            void registerAdvancedComponents();
    };
}
