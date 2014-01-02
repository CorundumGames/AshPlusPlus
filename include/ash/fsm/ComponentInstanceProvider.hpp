#ifndef COMPONENTINSTANCEPROVIDER_H
#define COMPONENTINSTANCEPROVIDER_H

#include <memory>

#include "Declarations.hpp"
#include "ash/fsm/IComponentProvider.hpp"

using std::shared_ptr;
using std::make_shared;


namespace ash {
namespace fsm {
/**
 * This component provider always returns the same instance of the component. The instance is passed to the provider at
 * initialisation.
 */
template<class C>
class ComponentInstanceProvider : public IComponentProvider<C, shared_ptr<C>>
{
    public:
        /**
         * Constructor
         *
         * @param instance The instance to return whenever a component is requested.
         */
        ComponentInstanceProvider(const shared_ptr<C> instance) : _instance(instance) {}

        /**
         * Used to request a component from this provider
         *
         * @return The instance
         */
        C const& getComponent() const {
            return *(this->_instance);
        }

        /**
         * Used to compare this provider with others. Any provider that returns the same component instance will be
         * regarded as equivalent.
         *
         * @return The instance
         */
        shared_ptr<C> const& identifier() const {
            return this->_instance;
        }
    private:
        shared_ptr<C> _instance;
};
}
}

#endif // COMPONENTINSTANCEPROVIDER_H
