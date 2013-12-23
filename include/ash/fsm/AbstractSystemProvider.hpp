#ifndef ABSTRACTSYSTEMPROVIDER_HPP
#define ABSTRACTSYSTEMPROVIDER_HPP

#include "ash/fsm/ISystemProvider.hpp"

namespace ash {
namespace fsm {
/**
 * An abstract variety of ISystemProvider.  All it does is fill in the priority.
 */
template<class C, class I>
class AbstractSystemProvider : public ISystemProvider<C, I>
{
    public:
        AbstractSystemProvider() : _priority(0) {}
        virtual ~AbstractSystemProvider() {}

        int priority() const {
            return this->_priority;
        };

        void priority(const int priority) {
            this->_priority = priority;
        };
    protected:
        int _priority;
};
}
}

#endif // ABSTRACTSYSTEMPROVIDER_HPP
