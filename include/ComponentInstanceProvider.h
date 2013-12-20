#ifndef COMPONENTINSTANCEPROVIDER_H
#define COMPONENTINSTANCEPROVIDER_H

#include <memory>

#include "Declarations.h"
#include "IComponentProvider.h"

using std::shared_ptr;
using std::make_shared;

/**
 * This component provider always returns the same instance of the component. The instance
 * is passed to the provider at initialisation.
 */
namespace ash {
    namespace fsm {
        template<class C>
        class ComponentInstanceProvider : public IComponentProvider<C, C>
        {
            public:
                /**
                 * Constructor
                 *
                 * @param instance The instance to return whenever a component is requested.
                 */
                ComponentInstanceProvider(const C& instance) : _instance(make_shared(instance)) {}
                virtual ~ComponentInstanceProvider() {}

                /**
                 * Used to request a component from this provider
                 *
                 * @return The instance
                 */
                C const& getComponent() const {
                    return *(this->_instance);
                }

                /**
                 * Used to compare this provider with others. Any provider that returns the same component
                 * instance will be regarded as equivalent.
                 *
                 * @return The instance
                 */
                C const& identifier() const {
                    return this->getComponent();
                }
            private:
                shared_ptr<C> _instance;
        };
    }
}

#endif // COMPONENTINSTANCEPROVIDER_H
