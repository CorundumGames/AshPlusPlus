#ifndef ENTITYCREATOR_HPP
#define ENTITYCREATOR_HPP

#include "ash/core/Entity.hpp"

using ash::core::Entity;

namespace net {
namespace richardlord {
namespace asteroids {
class EntityCreator
{
    public:
        EntityCreator();
        virtual ~EntityCreator();
        void destroyEntity(const Entity& entity);
};
}
}
}

#endif // ENTITYCREATOR_HPP
