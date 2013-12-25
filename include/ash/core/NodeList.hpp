#ifndef NODELIST_HPP
#define NODELIST_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include "Declarations.hpp"
#include "ash/core/Node.hpp"
#include "ash/signals/Signal.hpp"

using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::remove;

namespace ash {
namespace core {
/**
 * A collection of nodes.
 *
 * Systems within the engine access the components of entities via NodeLists. A NodeList contains a node for each Entity
 * in the engine that has all the components required by the node. To iterate over a NodeList, start from the head and
 * step to the next on each loop, until the returned value is null. Or just use for in syntax.
 *
 * for (auto node& : nodeList) {
 *   // do stuff
 * }
 *
 * It is safe to remove items from a nodelist during the loop. When a Node is removed form the NodeList it's previous
 * and next properties still point to the nodes that were before and after it in the NodeList just before it was removed.
 */
template<class T>
class NodeList
{
    public:
        NodeList() : nodeAdded(), nodeRemoved() {}

        /**
         * The first item in the node list, or nullptr if the list contains no nodes.
         */
        shared_ptr<T> head() const {
            return make_shared(this->_nodes.front());
        }

        /**
         * The last item in the node list, or null if the list contains no nodes.
         */
        shared_ptr<T> tail() const {
            return make_shared(this->_nodes.back());
        }

        /**
         * Returns true if this NodeList has no Nodes.
         */
        bool empty() const {
            return this->_nodes.empty();
        }

        void add(const T& node) {
            this->_nodes.push_back(node);
            this->nodeAdded.dispatch(node);
        }

        void remove(const T& node) {
            remove(this->_nodes.begin(), this->_nodes.end(), node);
            this->nodeRemoved.dispatch(node);
        }

        void removeAll() {
            for (const T& i : this->_nodes) {
                this->nodeRemoved.dispatch(i);
            }

            this->_nodes.clear();
        }

        void swap(const T& node1, const T& node2) {
        }

        auto begin() const {
            return this->_nodes.begin();
        }

        auto end() const {
            return this->_nodes.end();
        }


    private:
        vector<T> _nodes;
        Signal1<T> nodeAdded;
        Signal1<T> nodeRemoved;

};
}
}

#endif // NODELIST_HPP
