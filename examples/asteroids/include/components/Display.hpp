#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "ash/core/Component.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {

using std::shared_ptr;

using sf::Drawable;

using ash::core::Component;

struct Display : public Component
{
    Display(const shared_ptr<Drawable> display) : displayObject(display) {}
    shared_ptr<Drawable> displayObject;
};
}
}
}
}
#endif // DISPLAY_HPP
