#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <algorithm>
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <type_traits>

#include <boost/any.hpp>

#include "Declarations.hpp"
#include "ash/core/Entity.hpp"
#include "ash/core/System.hpp"
#include "ash/signals/Signal.hpp"
#include "ash/core/ComponentMatchingFamily.hpp"
#include "ash/core/SystemList.hpp"

namespace ash {
namespace core {

using std::list;
using std::string;
using std::shared_ptr;
using std::type_info;
using std::unordered_map;
using std::vector;
using std::stable_sort;
using std::is_base_of;
using std::is_same;
using std::enable_shared_from_this;

using boost::any;
using boost::any_cast;

using ash::core::Component;
using ash::core::Entity;
using ash::core::System;
using ash::core::ComponentMatchingFamily;
using ash::signals::Signal;
using ash::signals::Signal0;
using ash::signals::Signal1;

class Engine : public enable_shared_from_this<Engine>
{
    public:
        Engine() :
            _entities(),
            _systems(),
            _entity_names(),
            _families(),
            _update_complete(),
            _entity_added(),
            _entity_removed(),
            _updating(false)
        {
        }
        virtual ~Engine();

        /**
         * Add an entity to the engine.
         *
         * @param entity The entity to add.
         */
        void addEntity(const shared_ptr<Entity> entity);


        /**
         * Remove an Entity from the engine.
         *
         * @param entity The Entity to remove.
         */
        void removeEntity(shared_ptr<Entity> entity);

        /**
         * Get an entity based on its name.
         *
         * @param name The name of the \c Entity
         * @return The entity, or \c nullptr if no entity with that name exists in this \c Engine
         */
        shared_ptr<Entity> const getEntityByName(const string& name) const;

        /**
         * Remove all entities from the engine.
         */
        void removeAllEntities();

        /**
         * Add a system to the engine, and set its priority for the order in which the systems are updated by the engine
         * update loop.
         *
         * The priority dictates the order in which the systems are updated by the engine update loop. Lower numbers for
         * priority are updated first. i.e. a priority of 1 is updated before a priority of 2.
         *
         * @param system The system to add to the engine.
         * @param priority The priority for updating the systems during the engine loop. A lower number means the system
         * is updated sooner.
         */
        void addSystem(const shared_ptr<System> system, const int priority);

        template<class T>
        shared_ptr<T> getSystem() const;

        /**
         * Remove a system from the engine.
         *
         * @param system The system to remove from the engine.
         */
        void removeSystem(const shared_ptr<System> system);

        /**
         * Remove all systems from the engine.
         */
        void removeAllSystems();

        /**
         * Update the engine. This causes the engine update loop to run, calling update on all the
         * systems in the engine.
         *
         * The package ash.tick contains classes that can be used to provide
         * a steady or variable tick that calls this update method.
         *
         * @param time The duration, in seconds, of this update step.
         */
        void update(const double time);

        /**
         * Returns true if the engine is currently in its update loop.
         */
        bool updating() const;

        /**
         * Get a collection of nodes from the engine, based on the type of the node required.
         *
         * The engine will create the appropriate NodeList if it doesn't already exist and will keep its contents up to
         * date as entities are added to and removed from the engine.
         *
         * If a NodeList is no longer required, release it with the releaseNodeList method.
         *
         * @param nodeClass The type of node required.
         * @return A linked list of all nodes of this type from all entities in the engine.
         */
        template<class T>
        NodeList<T> getNodeList() {
            static_assert(is_base_of<Node, T>() && !is_same<Node, T>(), "You must pick a Node");

            type_index type(typeid(T));
            if (this->_families.count(type)) {
                return this->_families[type]->nodeList<T>();
            }

            shared_ptr<ComponentMatchingFamily> family(
                make_shared<ComponentMatchingFamily>(this->shared_from_this(), type_index(typeid(T)))
            );
            family->setNewNodeList<T>();
            this->_families[type] = family;

            for (shared_ptr<Entity> e : this->_entities) {
                family->newEntity(e);
            }

            return family->nodeList<T>();
            /*
            if (families.exists(nodeClass))
            return cast(families.get(nodeClass)).nodeList;

            var family:IFamily<TNode> = cast(Type.createInstance(familyClass, [nodeClass, this ]));
            families.set(nodeClass, family);

            for (entity in entityList)
            family.newEntity(entity);

            return family.nodeList;
            */
        }

        vector<shared_ptr<Entity>> entities() const {
            return vector<shared_ptr<Entity>>();
        }

        vector<shared_ptr<System>> systems() const {
            return vector<shared_ptr<System>>();
        }

        /**
         * Dispatched when the update loop ends. If you want to add and remove systems from the engine it is usually
         * best not to do so during the update loop. To avoid this you can listen for this signal and make the change
         * when the signal is dispatched.
         */
        Signal0 const& update_complete() const;

        Signal1<Entity> const& entity_added() const;

        Signal1<Entity> const& entity_removed() const;

    protected:
    private:
        list<shared_ptr<Entity>> _entities;
        list<shared_ptr<System>> _systems;
        unordered_map<string, shared_ptr<Entity>> _entity_names;
        unordered_map<type_index, shared_ptr<ComponentMatchingFamily>> _families;
        // ^ holds ComponentMatchingFamily<T>'s
        Signal0 _update_complete;
        Signal1<Entity> _entity_added;
        Signal1<Entity> _entity_removed;
        bool _updating;

        void componentAdded(const Entity&, const type_index&);
        void componentRemoved(const Entity&, const type_index&);
        void entityNameChanged(const Entity&, const string&);
};
}
}

#endif // ENGINE_H
