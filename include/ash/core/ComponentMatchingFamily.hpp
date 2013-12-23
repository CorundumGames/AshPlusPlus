#ifndef COMPONENTMATCHINGFAMILY_HPP
#define COMPONENTMATCHINGFAMILY_HPP

#include <unordered_map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <memory>

#include "Declarations.hpp"
#include "ash/core/IFamily.hpp"
#include "ash/core/Entity.hpp"
#include "ash/core/Engine.hpp"

using std::string;
using std::type_index;
using std::shared_ptr;
using std::make_shared;
using std::unordered_map;

namespace ash {
namespace core {
/**
 * The default class for managing a NodeList. This class creates the NodeList and adds and removes nodes to/from the
 * list as the entities and the components in the engine change.
 *
 * It uses the basic entity matching pattern of an entity system - entities are added to the list if they contain
 * components matching all the public properties of the node class.
 */
template<class T>
class ComponentMatchingFamily : public IFamily<T>
{
    public:
        /**
         * The constructor. Creates a ComponentMatchingFamily to provide a NodeList for the given node class.
         *
         * @param engine The engine that this family is managing the NodeList for.
         */
        ComponentMatchingFamily(const Engine& engine) :
            _engine(make_shared<Engine>(engine)),
            _entities(),
            _components()
        {

        }

        /**
         * Called by the engine when an entity has been added to it. We check if the entity should be in this family's
         * NodeList and add it if appropriate.
         */
        void newEntity(const Entity&) = 0;


        void removeEntity(const Entity&) = 0;


        void componentAddedToEntity(const Entity&, const type_info&) = 0;


        void componentRemoveFromEntity(const Entity&, const type_info&) = 0;

        /**
        * Removes all nodes from the NodeList.
        */
        void cleanUp() {
            for (const auto i : this->nodeList()) {
                this->_entities.remove(i.entity);
            }

            this->nodeList.removeAll();
        }

        /**
         * Returns the NodeList managed by this class. This should be a reference that remains valid always since it is
         * retained and reused by Systems that use the list. i.e. never recreate the list, always modify it in place.
         */
        NodeList<T> const& nodeList() const = 0;
    private:
        shared_ptr<Engine> _engine;
        unordered_map<shared_ptr<Entity>, Node<T>> _entities;
        unordered_map<type_index, string> _components;

        /**
         * If the entity is not in this family's NodeList, tests the components of the entity to see
         * if it should be in this NodeList and adds it if so.
         */
        void _add_if_match(const Entity& entity) {
            if (this->_entities.count(entity) <= 0) {
                // If we don't already have this entity on record...
                for (const auto& c : this->_components) {
                    if (!entity.has(c.first)) {
                        return;
                    }
                }
                /*
                var node:TNode = nodePool.get();
                node.entity = entity;
                for (componentClass in components.keys())
                {
                    Reflect.setField(node, components.get(componentClass), entity.get(componentClass));
                }
                entities.set(entity, node);
                nodeList.add(node);
                }
                }*/
            }
        }
};
}
}
#endif // COMPONENTMATCHINGFAMILY_HPP
