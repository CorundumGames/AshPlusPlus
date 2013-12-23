#include <stdexcept>
#include <typeinfo>

using std::invalid_argument;
using std::type_info;

#include "ash/core/Component.hpp"
#include "ash/core/Entity.hpp"

int ash::core::Entity::_nameCount = 0;

ash::core::Entity::Entity() : Entity(("_entity" + (++Entity::_nameCount))) {
}

ash::core::Entity::Entity(const std::string& name) :
    _componentAdded()  ,
    _componentRemoved(),
    _nameChanged()     ,
    _components()
{
    this->_name = (name.size() > 0) ? name : "_entity" + (++Entity::_nameCount);
}

ash::core::Entity::~Entity()
{
}

string ash::core::Entity::name() const {
    return this->_name;
}

void ash::core::Entity::name(const string& name) {
    if (this->_name != name) {
        // If the new name isn't the same as the current name...
        string previous = this->_name;
        this->_name = name;
        this->_nameChanged.dispatch(*this, previous);
    }
}

ash::core::Entity& ash::core::Entity::add(const shared_ptr<Component> component) {
    if (component == nullptr) {
        // If we never actually got a pointer to a Component...
        throw invalid_argument("Expected a pointer to a Component, received nullptr");
    }

    type_index type = type_index(typeid(Component));
    this->_components[type] = component;
    this->_componentAdded.dispatch(*this, type);
    return *this;
}

