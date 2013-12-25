#ifndef LISTITERATINGSYSTEM_HPP
#define LISTITERATINGSYSTEM_HPP

#include <functional>
#include <memory>

#include "Declarations.hpp"
#include "ash/core/System.hpp"

using std::shared_ptr;
using std::make_shared;
using std::function;

namespace ash {
namespace tools {
/**
 * A useful class for systems which simply iterate over a set of nodes, performing the same action on each node. This
 * class removes the need for a lot of boilerplate code in such systems. Extend this class and pass the node type and
 * a node update method into the constructor. The node update method will be called once per node on the update cycle
 * with the node instance and the frame time as parameters. e.g.
 *
 * <code>
 * template<class MyNode>
 * class MySystem : public ListIteratingSystem<MyNode>
 * {
 *     public function new()
 *     {
 *         super(MyNode, updateNode);
 *     }
 *
 *     private function updateNode(node:MyNode, time:Float):Void
 *     {
 *         // process the node here
 *     }
 * }
 * </code>
 */
template<class T>
class ListIteratingSystem : public System
{
    public:
        ListIteratingSystem(const function<void(T, double)>& nodeUpdateFunction) :
            _node_update_function(make_shared(nodeUpdateFunction)),
            _node_added_function(nullptr),
            _node_removed_function(nullptr),
            _nodes()
        {}

        ListIteratingSystem(const function<void(T, double)>& nodeUpdateFunction,
                            const function<void(T)>& nodeAddedFunction) :
            _node_update_function(make_shared(nodeUpdateFunction)),
            _node_added_function(make_shared(nodeAddedFunction)),
            _node_removed_function(nullptr),
            _nodes()
        {}

        ListIteratingSystem(const function<void(T, double)>& nodeUpdateFunction,
                            const function<void(T)>& nodeAddedFunction,
                            const function<void(T)>& nodeRemovedFunction) :
            _node_update_function(make_shared(nodeUpdateFunction)),
            _node_added_function(make_shared(nodeAddedFunction)),
            _node_removed_function(make_shared(nodeRemovedFunction)),
            _nodes()
        {}

        virtual ~ListIteratingSystem() {}
    protected:
        void addToEngine(Engine& engine) {
        }

        void removeFromEngine(Engine& engine) {}

        void update(const double time) {
        }
    private:
        shared_ptr<function<void(T, double)>> _node_update_function;
        shared_ptr<function<void(T)>> _node_added_function;
        shared_ptr<function<void(T)>> _node_removed_function;
        NodeList<T> _nodes;
};
}
}

#endif // LISTITERATINGSYSTEM_HPP
