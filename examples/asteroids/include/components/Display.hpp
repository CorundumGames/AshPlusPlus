#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "ash/core/Component.hpp"

using std::shared_ptr;

using sf::Drawable;

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
struct Display : public Component
{
    Display() {}
    shared_ptr<Drawable> displayObject;
};
}
}
}
}
#endif // DISPLAY_HPP
