#ifndef NODELIST_HPP
#define NODELIST_HPP

#include <iterator>
#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>
#include <type_traits>
#include <exception>
#include <sstream>

#include "Declarations.hpp"
#include "ash/signals/Signal.hpp"
#include "ash/core/Node.hpp"


namespace ash {
namespace core {
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::remove;
using std::iterator;
using std::bidirectional_iterator_tag;
using std::swap;
using std::is_base_of;
using std::is_same;
using std::invalid_argument;
using std::stringstream;

using ash::signals::Signal1;

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
        class NodeListIterator;
    public:
        NodeList() : _node_added(), _node_removed() {
            static_assert(is_base_of<Node, T>() && !is_same<Node, T>(), "NodeLists must contain Nodes");
        }
        ~NodeList() {}

        /**
         * The first item in the node list, or nullptr if the list contains no nodes.
         */
        shared_ptr<T> head() const {
            return shared_ptr<T>(this->_nodes.front());
        }

        /**
         * The last item in the node list, or null if the list contains no nodes.
         */
        shared_ptr<T> tail() const {
            return shared_ptr<T>(this->_nodes.back());
        }

        /**
         * Returns true if this NodeList has no Nodes.
         */
        bool empty() const {
            return this->_nodes.empty();
        }

        void add(const shared_ptr<T> node) {
            this->_nodes.push_back(node);
            this->_node_added.dispatch(*node);
        }

        void remove(const shared_ptr<T> node) {
            if (node == nullptr) {
                stringstream error;
                error << "Expected a shared pointer to a " << typeid(T).name() << ", got nullptr";
                throw invalid_argument(error.str());
            }
            std::remove(this->_nodes.begin(), this->_nodes.end(), node);
            this->_node_removed.dispatch(*node);
        }

        void removeAll() {
            for (const T& i : this->_nodes) {
                this->_node_removed.dispatch(i);
            }

            this->_nodes.clear();
        }

        void swap(shared_ptr<T> node1, shared_ptr<T> node2) {

        }

        void sort() {
        }

        NodeListIterator begin() {
            return NodeListIterator(&(this->_nodes.front()));
        }

        NodeListIterator end() {
            return NodeListIterator(&(this->_nodes.back()) + 1);
        }

        Signal1<T>& nodeAdded() {
            return this->_node_added;
        }

        Signal1<T>& nodeRemoved() {
            return this->_node_removed;
        }

    private:
        vector<shared_ptr<T>> _nodes;
        Signal1<T> _node_added;
        Signal1<T> _node_removed;
        class NodeListIterator : public iterator<bidirectional_iterator_tag, T> {
            public:
                NodeListIterator(shared_ptr<T>* p) : ptr(p) {}
                NodeListIterator(const NodeListIterator& other) = default;
                NodeListIterator(NodeListIterator&& other) = default;
                NodeListIterator& operator=(const NodeListIterator& other) = default;
                NodeListIterator& operator=(NodeListIterator&& other) = default;

                T& operator*() {
                    return **(this->ptr);
                }

                NodeListIterator& operator++() {
                    (this->ptr)++;
                    return *this;
                }

                NodeListIterator& operator++(const int) {
                    return this->operator++();
                }

                NodeListIterator& operator--() {
                    (this->ptr)--;
                    return *this;
                }

                NodeListIterator& operator--(const int) {
                    return this->operator--();
                }

                bool operator==(const NodeListIterator& other) const {
                    return this->ptr == other.ptr;
                }

                bool operator!=(const NodeListIterator& other) const {
                    return !(this->operator==(other));
                }
            private:
                shared_ptr<T>* ptr;
        };

};
}
}

#endif // NODELIST_HPP
