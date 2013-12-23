#ifndef DYNAMICSYSTEMPROVIDER_H
#define DYNAMICSYSTEMPROVIDER_H

#include <functional>

#include "AbstractSystemProvider.hpp"

using std::function;

namespace ash {
namespace fsm {
/**
 * This System provider returns results of a method call. The method is passed to the provider at initialisation.
 */
template<class C>
class DynamicSystemProvider : public AbstractSystemProvider<C, function<C(void)>>
{
    public:
        DynamicSystemProvider(const function<C(void)>& closure) : _closure(closure) {}
        virtual ~DynamicSystemProvider() {}

        /**
         * Used to compare this provider with others. Any provider that returns the same component instance will be
         * regarded as equivalent.
         *
         * @return The method used to call the System instances
         */
        C getSystem() {
            return this->_closure();
        }

        function<C(void)> const& identifier() const {
            return this->_closure;
        }
    private:
        function<C(void)> _closure;
};
}
}

#endif // DYNAMICSYSTEMPROVIDER_H
