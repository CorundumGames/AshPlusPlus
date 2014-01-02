#ifndef ENTITY_H
#define ENTITY_H

#include <functional>
#include <vector>
#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <typeindex>
#include <type_traits>

#include "Declarations.hpp"
#include "ash/core/Component.hpp"
#include "ash/signals/Signal.hpp"

using std::string;
using std::type_info;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::unordered_map;
using std::hash;
using std::type_index;
using std::make_shared;
using std::is_pointer;
using std::static_pointer_cast;

using ash::core::Engine;
using ash::signals::Signal2;


namespace ash {
namespace core {
/**
 * An entity is composed from components. As such, it is essentially a collection object for components. Sometimes, the
 * entities in a game will mirror the actual characters and objects in the game, but this is not necessary.
 *
 * Components are simple value objects that contain data relevant to the entity. Entities with similar functionality
 * will have instances of the same components. So we might have a position component:
 *
 * <code>struct PositionComponent
 * {
 *   float x;
 *   float y;
 * }</code>
 *
 * All entities that have a position in the game world, will have an instance of the position component. Systems operate
 * on entities based on the components they have.
 */
class Entity
{
        friend Engine;
    public:
        explicit Entity(const string&);
        Entity();
        virtual ~Entity();

        /**
         * Add a component to the entity.
         *
         * If the given component is an actual object, a copy will be added to this Entity.  If it is a pointer, the
         * component itself will be added to this Entity.
         *
         * @param component The component object to add.
         * @return A reference to the entity. This enables the chaining of calls to add, to make creating and
         * configuring entities cleaner. e.g.
         *
         * <code>
         * Entity entity = Entity()
         *     .add(new Position(100, 200)
         *     .add(new Display(new PlayerClip()
         * </code>
         */
        template<class T>
        Entity& add(const shared_ptr<T> component) {
            type_index type = type_index(typeid(T));
            this->_components[type] = component;
            this->_componentAdded.dispatch(*this, type);
            return *this;
        }

        /**
         * Remove a component from the entity.
         *
         * @param componentClass The class of the component to be removed.
         * @return the component, or null if the component doesn't exist in the entity
         */
        template<class T>
        shared_ptr<T> remove() {
            return nullptr;
        }

        /**
         * Get a component from the entity.
         *
         * @param componentClass The class of the component requested.
         * @return The component, or null if none was found.
         */
        template<class T>
        shared_ptr<T> get() {
            type_index type = type_index(typeid(T));
            auto ret = this->_components[type];
            return (this->has<T>()) ? static_pointer_cast<T>(ret) : nullptr;
        }

        /**
         * Get all components from the entity.
         *
         * @return An array containing all the components that are on the entity.
         */
        vector<shared_ptr<Component>> getAll() const {
            return vector<shared_ptr<Component>>();
        }

        /**
         * Does the entity have a component of a particular type.
         *
         * @return true if the entity has a component of the type, false if not.
         */
        template<class T>
        bool has() const {
            return this->_components.count(type_index(typeid(T)));
        }

        /**
         * Optional, give the entity a name. This can help with debugging and with serialising the entity.
         */
        string name() const;

        /**
         * Optional, give the entity a name. This can help with debugging and with serialising the entity.
         */
        void name(const string& name);

        Signal2<Entity, type_index>& componentAdded() {
            return this->_componentAdded;
        }

        Signal2<Entity, type_index>& componentRemoved() {
            return this->_componentRemoved;
        }

        Signal2<Entity, string>& nameChanged() {
            return this->_nameChanged;
        }
    private:
        string _name;
        Signal2<Entity, type_index> _componentAdded;
        Signal2<Entity, type_index> _componentRemoved;
        Signal2<Entity, string> _nameChanged;

        unordered_map<type_index, shared_ptr<Component>> _components;
        static int _nameCount;
};
}
}
#endif // ENTITY_H
