#ifndef STATESYSTEMMAPPING_H
#define STATESYSTEMMAPPING_H

#include <memory>

#include "Declarations.hpp"
#include "ash/fsm/EngineState.hpp"
#include "ash/fsm/ISystemProvider.hpp"



namespace ash {
namespace fsm {
using std::shared_ptr;

/**
 * Used by the SystemState class to create the mappings of Systems to providers via a fluent interface.
 */
template<class S>
class StateSystemMapping
{
    public:
        /**
         * Used internally, the constructor creates a component mapping. The constructor creates a
         * SystemSingletonProvider as the default mapping, which will be replaced by more specific mappings if other
         * methods are called.
         *
         * @param creatingState The SystemState that the mapping will belong to
         * @param type The System type for the mapping
         */
        StateSystemMapping(const shared_ptr<EngineState> creating_state, const shared_ptr<ISystemProvider> provider) :
            _creating_state(creating_state),
            _provider(provider)
        {}

        /**
         * Applies the priority to the provider that the System will be.
         *
         * @param priority The component provider to use.
         * @return This StateSystemMapping, so more modifications can be applied.
         */
        StateSystemMapping<S> const& withPriority(const int priority) {
            this->_provider->priority(priority);
            return *this;
        }

        StateSystemMapping<S> const& addInstance(const shared_ptr<System> system) {
            return this->_creating_state->addInstance(system);
        }

        StateSystemMapping<S> const& addSingleton() {
            return this->_creating_state->addSingleton();
        }

        StateSystemMapping<S> const& addMethod(function<C(void)> method) {
            return *this;
        }

        StateSystemMapping<S> const& addProvider(shared_ptr<ISystemProvider> provider) {
            return *this;
        }
    private:
        shared_ptr<EngineState> _creating_state;
        shared_ptr<ISystemProvider<System>> _provider;
};
}
}

#endif // STATESYSTEMMAPPING_H
