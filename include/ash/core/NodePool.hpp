#ifndef NODEPOOL_HPP
#define NODEPOOL_HPP

#include <iterator>
#include <memory>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <vector>

#include "Declarations.hpp"

using std::type_info;
using std::string;
using std::type_index;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::make_move_iterator;

namespace ash {
namespace core {
/**
* This internal class maintains a pool of deleted nodes for reuse by the framework. This reduces the overhead from
* object creation and garbage collection.
*
* Because nodes may be deleted from a NodeList while in use, by deleting Nodes from a NodeList while iterating through
* the NodeList, the pool also maintains a cache of nodes that are added to the pool but should not be reused yet. They
* are then released into the pool by calling the releaseCache method.
*/
template<class T>
class NodePool
{
    public:
        /**
         * Creates a pool for the given node class.
         */
        NodePool() : _cache(), _pool() {}
        virtual ~NodePool() {}

        /**
         * Fetches a node from the pool.
         */
        T& get() {
            if (this->_nodes.size()) {
                // If we have any nodes cached...
                T& element = this->_nodes.back();
                this->_nodes.pop_back();
                return element;
            }
            else {
                return T();
            }
        }

        /**
         * Adds a node to the pool.
         */
        void dispose(const shared_ptr<T> node) {
            node.reset();
            this->_pool.push_back(make_shared(node));
        }

        /**
         * Adds a node to the cache
         */
        void cache(const shared_ptr<T> node) {
            this->_cache.push_back(make_shared(node));
        }

        /**
         * Releases all nodes from the cache into the pool
         */
        void releaseCache() {
            this->_pool.insert(this->pool.end(), make_move_iterator(this->_cache.begin()),
                               make_move_iterator(this->_cache.end()));
            this->_cache.clear();
        }

    private:
        vector<shared_ptr<T>> _cache;
        vector<shared_ptr<T>> _pool;
};
}
}

#endif // NODEPOOL_HPP
