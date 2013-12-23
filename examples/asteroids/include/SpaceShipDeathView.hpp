#ifndef SPACESHIPDEATHVIEW_HPP
#define SPACESHIPDEATHVIEW_HPP

#include <SFML/Graphics.hpp>
#include "IAnimatable.hpp"

using sf::ConvexShape;
using sf::Color;

namespace net {
namespace richardlord {
namespace asteroids {
namespace graphics {
class SpaceshipDeathView : public ConvexShape, public IAnimatable
{
    public:
        SpaceshipDeathView() : ConvexShape() {}
        virtual ~SpaceshipDeathView() {}
        void animate(const double time) {}
};
}
}
}
}
#endif // SPACESHIPDEATHVIEW_HPP
