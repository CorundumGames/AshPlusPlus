#ifndef COMPONENTMATCHINGFAMILY_HPP
#define COMPONENTMATCHINGFAMILY_HPP

#include <unordered_map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <type_traits>

#include <boost/any.hpp>

#include "Declarations.hpp"
#include "ash/core/Entity.hpp"
#include "ash/core/Engine.hpp"
#include "ash/core/NodePool.hpp"
#include "ash/core/NodeList.hpp"
#include "ash/core/Node.hpp"

namespace ash {
namespace core {

using std::string;
using std::type_index;
using std::type_info;
using std::shared_ptr;
using std::make_shared;
using std::unordered_map;
using std::is_base_of;
using std::is_same;

using boost::any;
using boost::any_cast;

using ash::core::NodeList;

/**
 * Creates a NodeList and adds and removes nodes to/from the list as the entities and the components in the engine
 * change. In the original Ash, this inherited from an interface called \c IFamily, but it turned out to be way too
 * complicated to implement nicely in C++, due to polymorphism and templates not mixing well.
 *
 * Unfortunately, due to this lack of covariance and contravariance, the type of a ComponentMatchingFamily must be
 * passed in at runtime, and the individual methods must be templated.
 *
 * It uses the basic entity matching pattern of an entity system - entities are added to the list if they contain
 * components matching all the public properties of the node class.
 */
class ComponentMatchingFamily
{
    public:
        /**
         * The constructor. Creates a ComponentMatchingFamily to provide a NodeList for the given node class.
         *
         * @param engine The engine that this family is managing the NodeList for.
         */
        ComponentMatchingFamily(const shared_ptr<Engine> engine, const type_index& type) :
            _engine(engine),
            _entities(),
            _components(),
            _type(type),
            _nodes()
        {

        }

        template<class T>
        void setNewNodeList() {
            this->_nodes = NodeList<T>();
        }

        /**
         * Called by the engine when an entity has been added to it. We check if the entity should be in this family's
         * NodeList and add it if appropriate.
         */
        void newEntity(const shared_ptr<Entity> entity) {
            this->_add_if_match(entity);
        }

        /**
         * Called by the engine when an entity has been rmoved from it. We check if the entity is in this family's
         * NodeList and remove it if so.
         */
        void removeEntity(const shared_ptr<Entity> entity) {
            this->_remove_if_match(entity);
        }

        /**
         * Called by the engine when a component has been added to an entity. We check if the entity is not in this
         * family's NodeList and should be, and add it if appropriate.
         */
        void componentAddedToEntity(const shared_ptr<Entity> entity, const type_info& type) {
            this->_add_if_match(entity);
        }

        /**
         * Called by the engine when a component has been removed from an entity. We check if the removed component is
         * required by this family's NodeList and if so, we check if the entity is in this this NodeList and remove it
         * if so.
         */
        void componentRemovedFromEntity(const shared_ptr<Entity> entity, const type_info& type) {
            if (this->_components.count(type_index(type))) {
                // If we have the entity we're looking for...
                this->_remove_if_match(entity);
            }
        }

        /**
         * Removes all nodes from the NodeList.
         */
        template<class T>
        void cleanUp() {
            for (const auto i : this->nodeList<T>()) {
                this->_entities.erase(i.entity);
            }

            any_cast<NodeList<T>>(this->_nodes)->removeAll();
        }

        template<class T>
        NodeList<T> nodeList() {
            return any_cast<NodeList<T>>(this->_nodes);
        }
    private:
        any _nodes;
        shared_ptr<Engine> _engine;
        type_index _type;
        unordered_map<shared_ptr<Entity>, shared_ptr<Node>> _entities;
        unordered_map<type_index, string> _components;

        /**
         * If the entity is not in this family's NodeList, tests the components of the entity to see if it should be in
         * this NodeList and adds it if so.
         */
        void _add_if_match(const shared_ptr<Entity> entity) {
            if (this->_entities.count(entity) <= 0) {
                // If we don't already have this entity on record...
                for (const auto& c : this->_components) {
                    if (!entity->has(c.first)) {
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

        void _remove_if_match(const shared_ptr<Entity> entity) {
            /*
            if (entities.exists(entity))
        {
            var node:TNode = entities.get(entity);
            entities.remove(entity);
            nodeList.remove(node);
            if (engine.updating)
            {
                nodePool.cache(node);
                engine.updateComplete.add(releaseNodePoolCache);
            }
            else
            {
                nodePool.dispose(node);
            }
        }
        */
        }
};
}
}
#endif // COMPONENTMATCHINGFAMILY_HPP
