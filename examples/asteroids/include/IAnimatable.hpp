#ifndef IANIMATABLE_H
#define IANIMATABLE_H

namespace net {
namespace richardlord {
namespace asteroids {
namespace graphics {
class IAnimatable
{
    public:
        virtual void animate(const double time) = 0;

};
}
}
}
}

#endif // IANIMATABLE_H
