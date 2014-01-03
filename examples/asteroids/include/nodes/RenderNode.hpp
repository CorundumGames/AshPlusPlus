#ifndef RENDERNODE_HPP
#define RENDERNODE_HPP

#include <memory>

#include "ash/core/Node.hpp"

#include "asteroids/include/components/Display.hpp"
#include "asteroids/include/components/Position.hpp"

using std::shared_ptr;

using net::richardlord::asteroids::components::Display;
using net::richardlord::asteroids::components::Position;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
/**
 * Node for rendering. Note that here it demonstrates how nodes work:
 *
 * The component system treats all variables (both public and private) as links to required components and sets their
 * values on node initialization, while properties and functions are ignored completely and can be used to make the node
 * API more useful.
 **/
struct RenderNode : public Node
{
    shared_ptr<Position> position;
    shared_ptr<Display> display;
};
}
}
}
}

#endif // RENDERNODE_HPP
