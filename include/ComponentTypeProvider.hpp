#ifndef COMPONENTTYPEPROVIDER_H
#define COMPONENTTYPEPROVIDER_H

#include "Declarations.h"
#include "IComponentProvider.h"


namespace ash {
    namespace fsm {
        template<class C>
        class ComponentTypeProvider : public IComponentProvider<C, C>
        {
            public:
                ComponentTypeProvider();
                virtual ~ComponentTypeProvider();
            protected:
            private:
        };
    }
}

#endif // COMPONENTTYPEPROVIDER_H
