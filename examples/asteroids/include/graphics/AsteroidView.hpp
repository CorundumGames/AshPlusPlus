#ifndef ASTEROIDVIEW_H
#define ASTEROIDVIEW_H

#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using std::rand;
using std::sin;
using std::cos;

using sf::ConvexShape;
using sf::Color;
using sf::Vector2;


namespace net {
namespace richardlord {
namespace asteroids {
namespace graphics {
class AsteroidView : public ConvexShape
{
    public:
        AsteroidView(const double radius) : ConvexShape() {
            double angle = 0.0;
            this->setFillColor(Color.White);
            do {
                this->setPointCount(this->getPointCount() + 1);
                double length = (.75 * (rand() / RAND_MAX) * .25) * radius;
                this->setPoint(this->getPointCount() - 1, Vector2<double>(cos(angle) * length, sin(angle) * length));
                angle += rand() / RAND_MAX;
            } while (angle < M_PI * 2);
        }
};
}
}
}
}
#endif // ASTEROIDVIEW_H
