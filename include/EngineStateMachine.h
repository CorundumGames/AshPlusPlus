#ifndef ENGINESTATEMACHINE_H
#define ENGINESTATEMACHINE_H

#include <string>

#include "Declarations.h"

using std::string;

using ash::core::Engine;

namespace ash
{
    namespace fsm
    {
        class EngineStateMachine
        {
            public:
                EngineStateMachine(const Engine&);
                virtual ~EngineStateMachine();

                EngineStateMachine addState(const string&, const EngineState&);
                EngineState createState(const string&);
                void changeState(const string&);
            protected:
            private:
        };
    }
}

#endif // ENGINESTATEMACHINE_H
