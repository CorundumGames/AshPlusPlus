#ifndef POSITION_HPP
#define POSITION_HPP

#include <SFML/System/Vector2.hpp>
#include "ash/core/Component.hpp"

using sf::Vector2;

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
class Position : public Component
{
    public:
        Position(const double x, const double y, const double rotation) :
            position(x, y),
            rotation(rotation)
        {}
        Vector2<double> position;
        double rotation;
};
}
}
}
}
#endif // POSITION_HPP
