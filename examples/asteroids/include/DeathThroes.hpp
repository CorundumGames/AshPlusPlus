#ifndef DEATHTHROES_H
#define DEATHTHROES_H

#include "ash/core/Component.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
class DeathThroes : public Component
{
    public:
        explicit DeathThroes(const double duration) : countdown(duration);
        double countdown;

};
}
}
}
}

#endif // DEATHTHROES_H
