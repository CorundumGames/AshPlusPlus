#ifndef MOTIONCONTROLNODE_HPP
#define MOTIONCONTROLNODE_HPP

#include <memory>

#include "ash/core/Node.hpp"

#include "asteroids/include/components/Motion.hpp"
#include "asteroids/include/components/MotionControls.hpp"
#include "asteroids/include/components/Position.hpp"

using std::shared_ptr;

using net::richardlord::asteroids::components::Motion;
using net::richardlord::asteroids::components::MotionControls;
using net::richardlord::asteroids::components::Position;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
class MotionControlNode : public Node
{
    MotionControlNode() {}
    shared_ptr<Motion> motion;
    shared_ptr<MotionControls> controls;
    shared_ptr<Position> position;
};
}
}
}
}
#endif // MOTIONCONTROLNODE_HPP
