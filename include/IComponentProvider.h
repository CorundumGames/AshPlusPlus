#ifndef ICOMPONENTPROVIDER_H
#define ICOMPONENTPROVIDER_H

#include "Declarations.h"

namespace ash {
namespace fsm {
/**
 * This is the Interface for component providers. Component providers are used to supply components for states within an
 * EntityStateMachine. Ash includes three standard component providers, ComponentTypeProvider, ComponentInstanceProvider
 * and ComponentSingletonProvider. Developers may wish to create more.
 */
template<class C, class I>
class IComponentProvider
{
    public:
        /**
         * Used to request a component from the provider.
         *
         * @return A component for use in the state that the entity is entering
         */
        virtual C const& getComponent() = 0;

        /**
         * Returns an identifier that is used to determine whether two component providers will return the equivalent
         * components.
         *
         * If an entity is changing state and the state it is leaving and the state is entering have components of the
         * same type, then the identifiers of the component provders are compared. If the two identifiers are the same
         * then the component is not removed. If they are different, the component from the old state is removed and a
         * component for the new state is added.
         *
         * @return An object
         */
        virtual I const& identifier() const = 0;
};
}
}

#endif // ICOMPONENTPROVIDER_H
