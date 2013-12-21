#ifndef STATECOMPONENTMAPPING_H
#define STATECOMPONENTMAPPING_H

#include <typeindex>
#include <typeinfo>
#include <memory>

#include "Declarations.h"
#include "Component.h"
#include "EntityState.h"
#include "IComponentProvider.h"
#include "ComponentInstanceProvider.h"
#include "ComponentTypeProvider.hpp"
#include "DynamicComponentProvider.hpp"

using std::shared_ptr;
using std::make_shared;
using std::type_info;
using std::type_index;

using ash::core::Component;

namespace ash {
namespace fsm {
/**
 * Used by the EntityState class to create the mappings of components to providers via a fluent interface.
 */
template<class C>
class StateComponentMapping
{
    public:
        /**
         * Used internally, the constructor creates a component mapping. The constructor creates a ComponentTypeProvider
         * as the default mapping, which will be replaced by more specific mappings if other methods are called.
         *
         * @param creatingState The EntityState that the mapping will belong to
         */
        StateComponentMapping(const EntityState& creatingState) :
            _provider(nullptr),
            _creating_state(make_shared<EntityState>(creatingState)) {}
        virtual ~StateComponentMapping() {}

        /**
         * Creates a mapping for the component type to a specific component instance. A ComponentInstanceProvider is
         * used for the mapping.
         *
         * @param component The component instance to use for the mapping
         * @return This StateComponentMapping, so more modifications can be applied
         */
        StateComponentMapping const& withInstance(const C& component) {
            this->setProvider(make_shared<IComponentProvider<C>>(ComponentInstanceProvider<C>(component)));
            return *this;
        }

        /**
         * Creates a mapping for the component type to new instances of the provided type.
         * The type should be the same as or extend the type for this mapping. A ComponentTypeProvider
         * is used for the mapping.
         *
         * @param type The type of components to be created by this mapping
         * @return This ComponentMapping, so more modifications can be applied
         */
        StateComponentMapping const& withType(const type_info& type) {
            this->setProvider(make_shared<IComponentProvider<C>>(ComponentTypeProvider<C>(type)));
            return *this;
        }

        /**
         * Creates a mapping for the component type to a single instance of the provided type.  The instance is
         * not created until it is first requested. The type should be the same as or extend the type for this
         * mapping. A ComponentSingletonProvider is used for the mapping.
         *
         * @return This ComponentMapping, so more modifications can be applied
         */
        StateComponentMapping const& withSingleton() {
            this->setProvider(make_shared<IComponentProvider<C>>(ComponentSingletonProvider<C>(typeid(C))));
            return *this;
        }

        /**
         * Creates a mapping for the component type to a method call. A
         * DynamicComponentProvider is used for the mapping.
         *
         * @param method The method to return the component instance
         * @return This ComponentMapping, so more modifications can be applied
         */
        StateComponentMapping const& withMethod(function<C(void)> method) {
            this->setProvider(make_shared<IComponentProvider<C>>(function<C(void)>(method)));
            return *this;
        }

        /**
         * Creates a mapping for the component type to any ComponentProvider.
         *
         * @param provider The component provider to use.
         * @return This ComponentMapping, so more modifications can be applied.
         */
        StateComponentMapping const& withProvider(shared_ptr<IComponentProvider<Component>> provider) {
            this->setProvider(provider);
            return *this;
        }

        /**
         * Maps through to the add method of the EntityState that this mapping belongs to
         * so that a fluent interface can be used when configuring entity states.
         *
         * @param type The type of component to add a mapping to the state for
         * @return The new ComponentMapping for that type
         */
        StateComponentMapping const& add(const type_info& type) {
            return this->_creating_state->add(type);
        }
    private:
        shared_ptr<EntityState> _creating_state;
        shared_ptr<IComponentProvider<Component>> _provider;

        void setProvider(shared_ptr<IComponentProvider<Component>> provider) {
            this->provider = provider;
            this->_creating_state->_providers.set(type_index(typeid(C)), provider);
        }
};
}
}

#endif // STATECOMPONENTMAPPING_H
