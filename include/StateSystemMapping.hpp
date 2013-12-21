#ifndef STATESYSTEMMAPPING_H
#define STATESYSTEMMAPPING_H

#include <memory>

#include "Declarations.h"
#include "EngineState.h"
#include "ISystemProvider.hpp"

using std::shared_ptr;

namespace ash {
namespace fsm {
template<class S>
class StateSystemMapping
{
    public:
        StateSystemMapping(const EngineState& creating_state, const shared_ptr<ISystemProvider> provider) :
            _creating_state(creating_state),
            _provider(provider)
        {}
        virtual ~StateSystemMapping() {}

        StateSystemMapping<S> const& withPriority(const int priority) {
            this->_provider->priority(priority);
            return *this;
        }

        StateSystemMapping<S> const& addInstance(const System& system) {
            return this->_creating_state->addInstance(system);
        }

        StateSystemMapping<S> const& addSingleton() {
            return this->_creating_state->addSingleton();
        }
    private:
        shared_ptr<EngineState> _creating_state;
        shared_ptr<ISystemProvider<System>> _provider;
};
}
}

#endif // STATESYSTEMMAPPING_H
