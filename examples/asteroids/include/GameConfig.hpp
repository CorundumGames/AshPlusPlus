#ifndef GAMECONFIG_H
#define GAMECONFIG_H

namespace net {
namespace richardlord {
namespace asteroids {
struct GameConfig
{
    GameConfig(const double width, const double height) : width(width), height(height) {}
    double width;
    double height;
};
}
}
}

#endif // GAMECONFIG_H
