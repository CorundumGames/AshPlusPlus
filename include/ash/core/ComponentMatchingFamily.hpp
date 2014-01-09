#ifndef COMPONENTMATCHINGFAMILY_HPP
#define COMPONENTMATCHINGFAMILY_HPP

#include <memory>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <unordered_map>

#include <boost/any.hpp>

#include "Declarations.hpp"
#include "ash/core/Entity.hpp"
#include "ash/core/Engine.hpp"
#include "ash/core/NodePool.hpp"
#include "ash/core/NodeList.hpp"
#include "ash/core/Node.hpp"

namespace ash {
namespace core {

using std::is_base_of;
using std::is_same;
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::type_index;
using std::type_info;
using std::unordered_map;

using boost::any;
using boost::any_cast;

using ash::core::NodeList;
using ash::core::NodePool;

/**
 * Creates a NodeList and adds and removes nodes to/from the list as the entities and the components in the engine
 * change. In the original Ash, this inherited from an interface called \c IFamily, but it turned out to be way too
 * complicated to implement nicely in C++, due to polymorphism and templates not mixing well.
 *
 * It uses the basic entity matching pattern of an entity system - entities are added to the list if they contain
 * components matching all the public properties of the node class.
 */
template<class T>
class ComponentMatchingFamily
{
    public:
        /**
         * The constructor. Creates a ComponentMatchingFamily to provide a NodeList for the given node class.
         *
         * @param engine The engine that this family is managing the NodeList for.
         */
        ComponentMatchingFamily(const shared_ptr<Engine> engine) :
            _engine(engine),
            _entities(),
            _components(),
            _node_list(),
            _node_pool()
        {

        }

        void setNewNodeList() {
            this->_node_list = NodeList<T>();
            this->_node_pool = NodePool<T>();
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
        void cleanUp() {
            for (const auto i : this->nodeList()) {
                this->_entities.erase(i.entity);
            }

            any_cast<NodeList<T>>(this->_node_list)->removeAll();
        }

        NodeList<T> nodeList() {
            return any_cast<NodeList<T>>(this->_node_list);
        }
    private:
        any _node_list;
        any _node_pool;
        shared_ptr<Engine> _engine;
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

                shared_ptr<Node> node = this->_node_pool.getNode();
                node->entity = entity;
                node->set();
                this->_entities[entity] = node;
                any_cast<NodeList<Node>>(this->_node_list).add(node);
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

        friend Engine;
};
}
}
#endif // COMPONENTMATCHINGFAMILY_HPP
