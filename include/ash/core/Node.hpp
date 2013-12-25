#ifndef NODE_H
#define NODE_H

#include <memory>

#include "Declarations.hpp"
#include "ash/core/Entity.hpp"

using std::shared_ptr;

namespace ash {
namespace core {
/**
 * The base class for a node.
 *
 * A node is a set of different components that are required by a system.  A system can request a collection of nodes
 * from the engine. Subsequently the Engine object creates a node for every entity that has all of the components in the
 * node class and adds these nodes to the list obtained by the system. The engine keeps the list up to date as entities
 * are added to and removed from the engine and as the components on entities change.
 *
 * It is recommended that you give Nodes pointers (raw or smart) to their components, rather than direct ownership.
 */
class Node
{
    public:
        Node() : entity(nullptr) {}
        virtual ~Node() {}

        /**
         * Resets all components and/or nulls them.  Nulls out the entity pointer at a minimum, override to null any
         * components.
         */
        virtual void reset() {
            this->entity = nullptr;
        }

    protected:
        shared_ptr<Entity> entity;
};
}
}

#endif // NODE_H
