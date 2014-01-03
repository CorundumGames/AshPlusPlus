#ifndef ENTITYSTATE_H
#define ENTITYSTATE_H

#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <type_traits>

#include "Declarations.hpp"
#include "ash/fsm/StateComponentMapping.hpp"
#include "ash/core/Component.hpp"
#include "ash/fsm/IComponentProvider.hpp"



namespace ash {
namespace fsm {
using std::shared_ptr;
using std::unordered_map;
using std::type_info;
using std::type_index;
using std::is_base_of;
using std::is_same;

using ash::core::Component;

class EntityState
{
        friend StateComponentMapping<Component>;

    public:
        EntityState();
        virtual ~EntityState();

        template<class T>
        EntityState& add_type() {
            static_assert(is_base_of<Component, T>() && !is_same<Component, T>(),
                          "You must add a class that extends Component to this EntityState");
            this->_providers[type_index(typeid(T))] = make_shared<ComponentTypeProvider<T>>();
            return *this;
        }

        template<class T>
        EntityState& add_instance(const shared_ptr<T> instance) {
            this->_providers[type_index(typeid(T))] = make_shared<ComponentInstanceProvider<T>>(instance);
            return *this;
        }

        template<class T>
        EntityState& add_singleton() {
            static_assert(is_base_of<Component, T>() && !is_same<Component, T>(),
                          "You must add a class that extends Component to this EntityState");
            this->_providers[type_index(typeid(T))] = make_shared<ComponentSingletonProvider<T>>();
            return *this;
        }

        template<class T>
        EntityState& add_method() {

        }

        template<class T>
        EntityState& add_provider(const shared_ptr<IComponentProvider<T>> provider) {
            static_assert(is_base_of<Component, T>() && !is_same<Component, T>(),
                          "You must add a class that extends Component to this EntityState");
            this->_providers[type_index(typeid(T))] = provider;
            return *this;
        }
    private:
        unordered_map<type_index, shared_ptr<IComponentProvider<Component>>> _providers;
};
}
}

#endif // ENTITYSTATE_H
