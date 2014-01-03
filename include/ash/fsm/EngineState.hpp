#ifndef ENGINESTATE_H
#define ENGINESTATE_H

#include "ash/core/System.hpp"
#include "ash/fsm/ISystemProvider.hpp"
#include "ash/fsm/SystemInstanceProvider.hpp"
#include "ash/fsm/SystemSingletonProvider.hpp"
#include "ash/fsm/DynamicSystemProvider.hpp"

#include <type_traits>
#include <vector>
#include <typeinfo>
#include <memory>

namespace ash {
namespace fsm {
    using std::is_base_of;
using std::shared_ptr;
using std::vector;

using ash::core::System;
using ash::fsm::ISystemProvider;
using ash::fsm::SystemInstanceProvider;
using ash::fsm::SystemSingletonProvider;
using ash::fsm::DynamicSystemProvider;
using ash::fsm::DynamicSystemProviderClosure;

/**
* Represents a state for an EngineStateMachine. The state contains any number of SystemProviders which are used to add
* Systems to the Engine when this state is entered.
*/
class EngineState
{
    public:
        EngineState() {}

        /**
         * Creates a mapping for the System type to a specific System instance. A
         * SystemInstanceProvider is used for the mapping.
         *
         * @param system The System instance to use for the mapping
         * @return This StateSystemMapping, so more modifications can be applied
         */
        template<class T>
        EngineState& add_instance(const shared_ptr<System> instance) {
            return this->add_provider(make_shared<SystemInstanceProvider<T>>(instance));
        }

        template<class T>
        EngineState& add_singleton() {
            return this->add_provider(make_shared<SystemSingletonProvider<T>>());
        }

        template<class T>
        EngineState& add_method(const DynamicSystemProviderClosure<T>& closure) {

            return this->add_provider(make_shared<DynamicSystemProvider>(closure));
        }

        template<class T>
        EngineState& add_provider(const shared_ptr<ISystemProvider<T>> provider) {
            static_assert(is_base_of<System, T>(), "You must choose a type that derives from System");

            this->_providers.push_back(provider);
            return *this;
        }

    private:
        vector<shared_ptr<ISystemProvider<System>>> _providers;
};
}
}

#endif // ENGINESTATE_H
