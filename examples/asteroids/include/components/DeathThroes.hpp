#ifndef DEATHTHROES_H
#define DEATHTHROES_H

#include "ash/core/Component.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
struct DeathThroes : public Component
{
    explicit DeathThroes(const double duration) : countdown(duration) {}
    double countdown;
};
}
}
}
}

#endif // DEATHTHROES_H
