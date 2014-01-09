#ifndef MOTIONCONTROLS_H
#define MOTIONCONTROLS_H

#include <SFML/Window/Keyboard.hpp>
#include "ash/core/Component.hpp"


namespace net {
namespace richardlord {
namespace asteroids {
namespace components {

using sf::Keyboard;
typedef sf::Keyboard::Key Key;

class MotionControls : public Component
{
    public:
        MotionControls(const Key& left,
                       const Key& right,
                       const Key& accelerate,
                       const double accelerationRate,
                       const double rotationRate
                      ) :
            left(left),
            right(right),
            accelerate(accelerate),
            accelerationRate(accelerationRate),
            rotationRate(rotationRate)
        {}
        Key left;
        Key right;
        Key accelerate;
        double accelerationRate;
        double rotationRate;
};
}
}
}
}
#endif // MOTIONCONTROLS_H
