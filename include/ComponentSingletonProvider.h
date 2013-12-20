#ifndef COMPONENTSINGLETONPROVIDER_H
#define COMPONENTSINGLETONPROVIDER_H

#include <memory>

#include "Declarations.h"
#include "IComponentProvider.h"

using std::shared_ptr;

namespace ash {
    namespace fsm {
        template<class C>
        class ComponentSingletonProvider : public IComponentProvider<C, C>
        {
            public:
                ComponentSingletonProvider() {}
                virtual ~ComponentSingletonProvider() {}

                C const& getComponent() override {
                    if (this->_instance == nullptr) {
                        *(this->_instance) = C();
                    }
                    return *(this->_instance);
                }

                C const& identifier() override {
                    return this->getComponent();
                }
            private:
                shared_ptr<C> _instance;
        };
    }
}

#endif // COMPONENTSINGLETONPROVIDER_H
