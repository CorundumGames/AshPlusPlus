#ifndef SYSTEMLIST_HPP
#define SYSTEMLIST_HPP

#include <algorithm>
#include <set>
#include <memory>

#include "Declarations.hpp"
#include "ash/core/System.hpp"

using std::find_if;
using std::set;
using std::shared_ptr;
using std::make_shared;

namespace ash {
namespace core {
/**
 * Used internally, this is an ordered list of Systems for use by the engine update loop.
 */
class SystemList
{
    private:
        set<shared_ptr<System>> _systems;
    public:
        SystemList() : _systems() {}
        virtual ~SystemList() {}

        void add(shared_ptr<System> system) {
            this->_systems.insert(shared_ptr<System>(&system));
        }

        void remove(shared_ptr<System> system) {
            this->_systems.erase(shared_ptr<System>(&system));
        }

        void removeAll() {
            this->_systems.clear();
        }

        template<class T>
        shared_ptr<T> get() {
            return find_if(this->_systems.begin(), this->_systems.end(), [&](const shared_ptr<System> ptr) {
                return typeid(ptr) == typeid(shared_ptr<T>);
            });
        }

        auto begin() -> decltype(_systems.begin()) {
            return this->_systems.begin();
        }

        auto end() -> decltype(_systems.begin()) {
            return this->_systems.end();
        }
};

}
}

#endif // SYSTEMLIST_HPP
