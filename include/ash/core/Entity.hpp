#ifndef ENTITY_H
#define ENTITY_H

#include <functional>
#include <vector>
#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <typeindex>

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

using ash::core::Engine;
using ash::signals::Signal2;


namespace ash {
namespace core {

class Entity
{
    friend Engine;
    public:
        Entity(const string&);
        Entity();
        virtual ~Entity();

        /**
         * Add a component to the entity.
         *
         * @param component The component object to add.
         *
         * @return A reference to the entity. This enables the chaining of calls to add, to make
         * creating and configuring entities cleaner. e.g.
         *
         * <code>var entity:Entity = new Entity()
         *     .add(new Position(100, 200)
         *     .add(new Display(new PlayerClip());</code>
         */
        Entity& add(const shared_ptr<Component> component);
        unique_ptr<Component> remove(const type_info&);
        Component& get(const type_info&) const;
        vector<shared_ptr<Component>> getAll() const;

        bool has(const type_info&) const;
        bool has(const type_index&) const;
        string name() const;
        void name(const string& name);


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
