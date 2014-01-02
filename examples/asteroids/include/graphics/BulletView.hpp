#ifndef BULLETVIEW_HPP
#define BULLETVIEW_HPP

#include <SFML/Graphics.hpp>

using sf::CircleShape;
using sf::Color;

namespace net {
namespace richardlord {
namespace asteroids {
namespace graphics {
class BulletView : public CircleShape
{
    public:
        BulletView() : CircleShape(2) {
            this->setFillColor(Color.White);
        }
};
}
}
}
}
#endif // BULLETVIEW_HPP
