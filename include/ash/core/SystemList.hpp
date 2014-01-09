#ifndef SYSTEMLIST_HPP
#define SYSTEMLIST_HPP

#include <algorithm>
#include <set>
#include <memory>

#include "Declarations.hpp"
#include "ash/core/System.hpp"


namespace ash {
namespace core {

using std::find_if;
using std::multiset;
using std::set;
using std::shared_ptr;
using std::make_shared;

/**
 * Used internally, this is an ordered list of Systems for use by the engine update loop.
 */
class SystemList
{
    private:
        multiset<shared_ptr<System>> _systems;
    public:
        SystemList();
        ~SystemList();

        void add(const shared_ptr<System> system);

        void remove(const shared_ptr<System> system);

        void removeAll();

        template<class T>
        shared_ptr<T> get() {
            return find_if(this->_systems.begin(), this->_systems.end(), [&](const shared_ptr<System> ptr) {
                return typeid(ptr) == typeid(shared_ptr<T>);
            });
        }

        auto begin() -> decltype(_systems.begin());

        auto end() -> decltype(_systems.begin());

};

}
}

#endif // SYSTEMLIST_HPP
