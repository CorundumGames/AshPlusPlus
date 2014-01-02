#ifndef LISTITERATINGSYSTEM_HPP
#define LISTITERATINGSYSTEM_HPP

#include <functional>
#include <memory>

#include "Declarations.hpp"
#include "ash/core/System.hpp"
#include "ash/core/NodeList.hpp"

using std::shared_ptr;
using std::make_shared;
using std::function;

using ash::core::NodeList;
using ash::core::System;

namespace ash {
namespace tools {
/**
 * A useful class for systems which simply iterate over a set of nodes, performing the same action on each node. This
 * class removes the need for a lot of boilerplate code in such systems. Extend this class and pass the node type and
 * a node update method into the constructor. The node update method will be called once per node on the update cycle
 * with the node instance and the frame time as parameters.
 *
 * Unlike in the original Ash, you can't pass in a method or function to call to the constructor, since passing around
 * functions and methods is simply too much of a pain in the ass in C++.  Use inheritance instead.
 */
template<class T>
class ListIteratingSystem : public System
{
    public:
        ListIteratingSystem() : _nodes() {}

        virtual ~ListIteratingSystem() {}
    protected:
        virtual void addToEngine(Engine& engine) override {
        }

        virtual void removeFromEngine(Engine& engine) override {}

        void update(const double time) override {

            for (T i : this->_nodes) {
                this->updateNode(i, time);
            }

        }

        virtual void updateNode(T& node, const double time) = 0;

        virtual void nodeAdded(T& node) {
        }

        virtual void nodeRemoved(T& node) {
        }
    private:
        NodeList<T> _nodes;
};
}
}

#endif // LISTITERATINGSYSTEM_HPP
