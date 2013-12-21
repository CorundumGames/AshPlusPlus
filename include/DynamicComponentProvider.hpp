#ifndef DYNAMICCOMPONENTPROVIDER_HPP
#define DYNAMICCOMPONENTPROVIDER_HPP

#include <functional>

#include "IComponentProvider.h"

using std::function;

namespace ash {
namespace fsm {

/**
 * This component provider calls a function to get the component instance. The function must return a single component
 * of the appropriate type.
 */
template<class C>
class DynamicComponentProvider : public IComponentProvider<C, function<C(void)>>
{
    public:
        /**
         * Constructor
         *
         * @param closure The function that will return the component instance when called.
         */
        DynamicComponentProvider(const function<C(void)>& closure) :
            _closure(closure) {}
        virtual ~DynamicComponentProvider() {}

        /**
         * Used to request a component from this provider
         *
         * @return The instance returned by calling the function
         */
        C getComponent() const {
            return this->_closure();
        }

        /**
         * Used to compare this provider with others. Any provider that uses the function or method closure to provide
         * the instance is regarded as equivalent.
         *
         * @return The function
         */
        function<C(void)> const& identifier() const {
            return this->_closure;
        }

    private:
        function<C(void)> _closure;
};
}
}
#endif // DYNAMICCOMPONENTPROVIDER_HPP
