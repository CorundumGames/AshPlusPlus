#include <exception>
#include <memory>
#include <functional>
#include <algorithm>

#include "ash/core/Entity.hpp"
#include "ash/core/Engine.hpp"

using std::find;
using std::function;
using std::logic_error;
using std::invalid_argument;
using std::shared_ptr;
using std::make_shared;
using std::bind;

using ash::core::Entity;
using boost::any;
using boost::any_cast;

using namespace std::placeholders;


ash::core::Engine::~Engine() {
}

void ash::core::Engine::addEntity(const shared_ptr<Entity> entity) {
    if (entity == nullptr) {
        // If we never actually got an Entity...
        throw invalid_argument("Expected a pointer to an entity, received nullptr");
    } else if (this->_entity_names.count(entity->name())) {
        // If we already have an Entity with this name...
        throw logic_error("Entity with name " + entity->name() + " already exists, names must be unique");
    }

    this->_entities.push_back(entity);
    this->_entity_names[entity->name()] = entity;

    entity->_componentAdded.add(bind(&ash::core::Engine::componentAdded, this, _1, _2));
    entity->_componentRemoved.add(bind(&ash::core::Engine::componentRemoved, this, _1, _2));
    entity->_nameChanged.add(bind(&ash::core::Engine::entityNameChanged, this, _1, _2));
    for (const auto& family : _families) {
        family.second->newEntity(entity);
    }

    this->_entity_added.dispatch(*entity);
}

void ash::core::Engine::removeEntity(shared_ptr<Entity> entity) {
    entity->_componentAdded.remove(bind(&ash::core::Engine::componentAdded, this, _1, _2));
    entity->_componentRemoved.remove(bind(&ash::core::Engine::componentRemoved, this, _1, _2));
    entity->_nameChanged.remove(bind(&ash::core::Engine::entityNameChanged, this, _1, _2));
    for (const auto& family : _families) {
        family.second->removeEntity(entity);
    }
    this->_entities.remove(entity);
    this->_entity_names.erase(entity->name());
    this->_entity_removed.dispatch(*entity);
}

void ash::core::Engine::removeAllEntities() {
    for (const shared_ptr<Entity> i : this->_entities) {
        this->_entity_names.erase(i->name());
        this->_entity_removed.dispatch(*i);
    }

    this->_entities.clear();
}


shared_ptr<Entity> const ash::core::Engine::getEntityByName(const string& name) const {
    if (this->_entity_names.count(name)) {
        // If we have the element whose name we're looking for...
        return this->_entity_names.at(name);
    }
    else {
        return nullptr;
    }
}

void ash::core::Engine::addSystem(const shared_ptr<System> system, const int priority) {
    system->priority(priority);
    system->addToEngine(this->shared_from_this());
    this->_systems.push_back(system);
    this->_systems.sort();
}

void ash::core::Engine::removeSystem(const shared_ptr<System> system) {
    this->_systems.remove(system);
    system->removeFromEngine(shared_ptr<Engine>(this));
}

void ash::core::Engine::removeAllSystems() {
    for (const shared_ptr<System> i : this->_systems) {
        i->removeFromEngine(shared_ptr<Engine>(this));
    }

    this->_systems.clear();
}

void ash::core::Engine::update(const double time) {
    this->_updating = true;
    for (const shared_ptr<System> i : this->_systems) {
        i->update(time);
    }
    this->_updating = false;
    this->_update_complete.dispatch();
}

void ash::core::Engine::componentAdded(const Entity& entity, const type_index& type) {
}

void ash::core::Engine::componentRemoved(const Entity& entity, const type_index& type) {
}

void ash::core::Engine::entityNameChanged(const Entity& entity, const string& type) {
}
