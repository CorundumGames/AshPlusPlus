#ifndef COMPONENTSINGLETONPROVIDER_H
#define COMPONENTSINGLETONPROVIDER_H

#include <memory>

#include "Declarations.hpp"
#include "ash/fsm/IComponentProvider.hpp"

using std::shared_ptr;

namespace ash {
namespace fsm {
/**
 * This component provider always returns the same instance of the component. The instance is created when first
 * required and is of the type passed in to the template.
 */
template<class C>
class ComponentSingletonProvider : public IComponentProvider<C, C>
{
    public:
        /**
         * Constructor
         */
        ComponentSingletonProvider() {}

        virtual ~ComponentSingletonProvider() {}

        /**
         * Used to request a component from this provider
         *
         * @return The single instance
         */
        C const& getComponent() override {
            if (this->_instance == nullptr) {
                *(this->_instance) = C();
            }
            return *(this->_instance);
        }

        /**
         * Used to compare this provider with others. Any provider that returns the same single
         * instance will be regarded as equivalent.
         *
         * @return The single instance
         */
        C const& identifier() override {
            return this->getComponent();
        }
    private:
        shared_ptr<C> _instance;
};
}
}

#endif // COMPONENTSINGLETONPROVIDER_H
