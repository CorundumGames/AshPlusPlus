#ifndef SYSTEMPRIORITIES_HPP
#define SYSTEMPRIORITIES_HPP

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {
namespace SystemPriorities {
enum {
    PRE_UPDATE = 1,
    UPDATE,
    MOVE,
    RESOLVE_COLLISIONS,
    STATE_MACHINES,
    ANIMATE,
    RENDER,
};
}
}
}
}
}
#endif // SYSTEMPRIORITIES_HPP
