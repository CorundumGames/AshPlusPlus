#ifndef IFAMILY_H
#define IFAMILY_H

#include <typeinfo>

#include "Definitions.h"

using std::type_info;

namespace ash {
    namespace core {
        class IFamily
        {
            public:
                void newEntity(const Entity&) = 0;
                void removeEntity(const Entity&) = 0;
                void componentAddedToEntity(const Entity&, const type_info&) = 0;
                void componentRemoveFromEntity(const Entity&, cont type_info&) = 0;\
                void cleanUp() = 0;
            protected:
            private:
        };
    }
}

#endif // IFAMILY_H
