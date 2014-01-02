#ifndef DEATHTHROESNODE_HPP
#define DEATHTHROESNODE_HPP

#include <memory>

#include "ash/core/Node.hpp"

#include "asteroids/include/components/DeathThroes.hpp"

using std::shared_ptr;

using net::richardlord::asteroids::components::DeathThroes;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
struct DeathThroesNode : public Node
{
    DeathThroesNode() {}
    shared_ptr<DeathThroes> death;
};
}
}
}
}

#endif // DEATHTHROESNODE_HPP
