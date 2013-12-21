#ifndef SYSTEMINSTANCEPROVIDER_H
#define SYSTEMINSTANCEPROVIDER_H

#include <memory>

#include "Declarations.h"
#include "AbstractSystemProvider.hpp"

using std::shared_ptr;

namespace ash {
namespace fsm {
/**
 * This System provider always returns the same instance of the component. The system is passed to the provider at
 * initialisation.
 */
template<class C>
class SystemInstanceProvider : public AbstractSystemProvider<C, C>
{
    public:
        SystemInstanceProvider(const C& instance) : _instance(instance) {}

        /**
         * Used to request a System from this provider
         *
         * @return The single instance
         */
        C getSystem() {
            return *(this->_instance);
        }

        /**
         * Used to compare this provider with others. Any provider that returns the same component instance will be
         * regarded as equivalent.
         *
         * @return The instance
         */
        C const& identifier() const {
            return this->getSystem();
        }
    private
        shared_ptr<C> _instance;
};
}
}

#endif // SYSTEMINSTANCEPROVIDER_H
