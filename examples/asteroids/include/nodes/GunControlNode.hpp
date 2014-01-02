#ifndef GUNCONTROLNODE_HPP
#define GUNCONTROLNODE_HPP

#include <memory>

#include "ash/core/Node.hpp"

#include "asteroids/include/components/Gun.hpp"
#include "asteroids/include/components/GunControls.hpp"
#include "asteroids/include/components/Position.hpp"

using std::shared_ptr;

using net::richardlord::asteroids::nodes::GunControls;
using net::richardlord::asteroids::nodes::Gun;
using net::richardlord::asteroids::nodes::Position;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
struct GunControlNode : public Node
{
    GunControlNode() {}
    shared_ptr<GunControls> control;
    shared_ptr<Gun> gun;
    shared_ptr<Position> position;
};
}
}
}
}
#endif // GUNCONTROLNODE_HPP
