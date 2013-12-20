#ifndef GUN_H
#define GUN_H

#include <SFML/System/Vector2.hpp>

#include "Component.h"

using sf::Vector2;

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
class Gun : public Component
{
    public:
        Gun(const double offsetX,
            const double offsetY,
            const double minimumShotInterval,
            const double bulletLifeTime) :
            timeSinceLastShot(0.0),
            minimumShotInterval(minimumShotInterval),
            bulletLifeTime(bulletLifeTime),
            offsetFromParent(offsetX, offsetY),
            shooting(false)
        {};
        virtual ~Gun();

        double timeSinceLastShot;
        double minimumShotInterval;
        double bulletLifeTime;
        Vector2<double> offsetFromParent;
        bool shooting;
};
}
}
}
}

#endif // GUN_H
