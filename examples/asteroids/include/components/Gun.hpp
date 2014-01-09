#ifndef GUN_H
#define GUN_H

#include <SFML/System/Vector2.hpp>

#include "ash/core/Component.hpp"


namespace net {
namespace richardlord {
namespace asteroids {
namespace components {

using sf::Vector2;

using ash::core::Component;

class Gun : public Component
{
    public:
        Gun(const double offsetX,
            const double offsetY,
            const double minimumShotInterval,
            const double bulletLifeTime) :
            offsetFromParent(offsetX, offsetY),
            timeSinceLastShot(0.0),
            minimumShotInterval(minimumShotInterval),
            bulletLifeTime(bulletLifeTime),
            shooting(false)
        {}

        Vector2<double> offsetFromParent;
        double timeSinceLastShot;
        double minimumShotInterval;
        double bulletLifeTime;
        bool shooting;
};
}
}
}
}

#endif // GUN_H
