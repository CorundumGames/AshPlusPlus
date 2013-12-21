#ifndef COMPONENTTYPEPROVIDER_H
#define COMPONENTTYPEPROVIDER_H

#include <typeinfo>

#include "Declarations.h"
#include "IComponentProvider.h"

using std::type_info;

namespace ash {
namespace fsm {
/**
 * This component provider always returns a new instance of a component. An instance is created when requested and is of
 the type passed in to the template.
 */
template<class C>
class ComponentTypeProvider : public IComponentProvider<C, type_info>
{
    public:
        ComponentTypeProvider();
        virtual ~ComponentTypeProvider();

        /**
         * Used to request a component from this provider
         *
         * @return A new instance of the type provided in the template
         */
        C getComponent() const {
            return C();
        }

        /**
         * Used to compare this provider with others. Any ComponentTypeProvider that returns
         * the same type will be regarded as equivalent.
         *
         * @return The type of the instances created
         */
        type_info const& identifier() const {
            return typeid(*this);
        }
};
}
}

#endif // COMPONENTTYPEPROVIDER_H
