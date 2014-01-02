#ifndef SPACESHIPVIEW_HPP
#define SPACESHIPVIEW_HPP

#include <SFML/Graphics.hpp>

using sf::ConvexShape;
using sf::Color;
using sf::Vector2f;

namespace net {
namespace richardlord {
namespace asteroids {
namespace graphics {
class SpaceShipView : public ConvexShape
{
    public:
        SpaceShipView() : ConvexShape(4) {
            this->setFillColor(Color.White);
            this->setPoint(0, Vector2f(10, 0));
            this->setPoint(1, Vector2f(-7, 7));
            this->setPoint(2, Vector2f(-4, 0));
            this->setPoint(3, Vector2f(-7, -7));
        }
};
}
}
}
}
#endif // SPACESHIPVIEW_HPP
