#ifndef SYSTEMSINGLETONPROVIDER_H
#define SYSTEMSINGLETONPROVIDER_H

#include <memory>

#include "AbstractSystemProvider.hpp"

using std::shared_ptr;

namespace ash {
namespace fsm {
template<class C>
class SystemSingletonProvider : public AbstractSystemProvider<C, C>
{
    public:
        SystemSingletonProvider() : _instance(nullptr) {}
        ~SystemSingletonProvider() {}

        C getSystem() {
            if (this->_instance == nullptr) {
                this->_instance = new C;
            }

            return *(this->_instance);
        }

        C const& identifier() const {
            return this->getSystem();
        }
    private:
        shared_ptr<C> _instance;
};
}
}

#endif // SYSTEMSINGLETONPROVIDER_H
