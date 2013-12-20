#ifndef DYNAMICCOMPONENTPROVIDER_HPP
#define DYNAMICCOMPONENTPROVIDER_HPP

#include <functional>

#include "IComponentProvider.h"

using std::function;

namespace ash {
    namespace fsm {
        template<class C> using DynamicComponentProviderClosure = function<C(void)>;

        template<class C>
        class DynamicComponentProvider : public IComponentProvider<C, C>
        {
            public:
                DynamicComponentProvider(DynamicComponentProviderClosure<C> closure) :
                    _closure(closure) {}
                virtual ~DynamicComponentProvider() {}
            private:
                DynamicComponentProviderClosure<C> _closure;
        };

    }
}
#endif // DYNAMICCOMPONENTPROVIDER_HPP
