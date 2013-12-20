#ifndef ENTITYSTATE_H
#define ENTITYSTATE_H

#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#include "Declarations.h"
#include "StateComponentMapping.h"
#include "Component.h"
#include "IComponentProvider.h"

using std::shared_ptr;
using std::unordered_map;
using std::type_info;
using std::type_index;

using ash::core::Component;

namespace ash {
    namespace fsm {
        class EntityState
        {
                friend StateComponentMapping<Component>;

            public:
                EntityState();
                virtual ~EntityState();

                template<class C>
                StateComponentMapping<C> add() {
                    return StateComponentMapping<C>(*this);
                }
            protected:
            private:
                unordered_map<type_index, shared_ptr<IComponentProvider<Component>>> _providers;
        };
    }
}

#endif // ENTITYSTATE_H
