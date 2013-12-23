#ifndef COMPONENTPOOL_H
#define COMPONENTPOOL_H

#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <memory>

using std::unordered_map;
using std::type_info;
using std::type_index;
using std::vector;
using std::shared_ptr;
using std::make_shared;

namespace ash {
namespace tools {
/**
 * An object pool for re-using components. This is not integrated in to Ash but is used dierectly by the developer. It
 * expects components to not require any parameters in their constructor.
 *
 * <p>Fetch an object from the pool with</p>
 *
 * <p>ComponentPool.get(ComponentClass);</p>
 *
 * <p>If the pool contains an object of the required type, it will be returned. If it does not, a new object
 * will be created and returned.</p>
 *
 * <p>The object returned may have properties set on it from the time it was previously used, so all properties
 * should be reset in the object once it is received.</p>
 *
 * <p>Add an object to the pool with</p>
 *
 * <p>ComponentPool.dispose(component);</p>
 *
 * <p>You will usually want to do this when removing a component from an entity. The remove method on the entity
 * returns the component that was removed, so this can be done in one line of code like this</p>
 *
 * <p>ComponentPool.dispose(entity.remove(component));</p>
 */
template<class T>
class ComponentPool {
public:
    static T get() {
        if (_pool.empty()) {
            return T();
        }
        else {
            return *(_pool.pop_back());
        }
    }

    static void dispose(const T& component) {
        _pool.push_back(make_shared<T>(component));
    }

    static void empty() {
        _pool.clear();
    }
private:
    static vector<shared_ptr<T>> _pool;

    ComponentPool() = delete;
};
}
}

#endif // COMPONENTPOOL_H
