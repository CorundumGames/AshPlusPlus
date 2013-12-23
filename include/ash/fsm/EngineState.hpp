#ifndef ENGINESTATE_H
#define ENGINESTATE_H

#include <typeinfo>

using std::type_info;

namespace ash {
    namespace fsm {
        class EngineState
        {
            public:
                EngineState();
                virtual ~EngineState();

                bool has(const type_info&);
            protected:
            private:
        };
    }
}

#endif // ENGINESTATE_H
