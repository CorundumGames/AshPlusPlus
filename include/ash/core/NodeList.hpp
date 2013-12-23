#ifndef NODELIST_HPP
#define NODELIST_HPP

#include <memory>
#include <vector>

#include "Declarations.hpp"
#include "ash/core/Node.hpp"
#include "ash/signals/Signal.hpp"

using std::shared_ptr;
using std::vector;

namespace ash {
namespace core {
/**
 * A collection of nodes.
 *
 * Systems within the engine access the components of entities via NodeLists. A NodeList contains
 * a node for each Entity in the engine that has all the components required by the node. To iterate
 * over a NodeList, start from the head and step to the next on each loop, until the returned value
 * is null. Or just use for in syntax.
 *
 * <p>for (auto node& : nodeList)
 * {
 *   // do stuff
 * }</p>
 *
 * It is safe to remove items from a nodelist during the loop. When a Node is removed form the
 * NodeList it's previous and next properties still point to the nodes that were before and after
 * it in the NodeList just before it was removed.
 */
template<class T>
class NodeList
{
    public:
        NodeList() : nodeAdded(), nodeRemoved() {}

        /**
         * The first item in the node list, or nullptr if the list contains no nodes.
         */
        shared_ptr<Node<T>> head() const;

        /**
         * The last item in the node list, or null if the list contains no nodes.
         */
        shared_ptr<Node<T>> tail() const;

        bool empty() const {
            return this->_nodes.empty();
        }

        void add(const Node<T>& node);

        void remove(const Node<T>& node);

        void removeAll() {
        }

        void swap(const Node<T>& node1, const Node<T>& node2) {
        }

        auto begin() const {
            return this->_nodes.begin();
        }


    private:
        vector<Node<T>> _nodes;
        Signal1<Node<T>> nodeAdded;
        Signal1<Node<T>> nodeRemoved;

};
}
}

#endif // NODELIST_HPP
