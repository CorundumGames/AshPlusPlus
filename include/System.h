#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>
#include <utility>

#include "Declarations.h"

using std::unique_ptr;
using namespace std::rel_ops;

namespace ash {
    namespace core {

        /**
         * The base class for a system.
         *
         * A system is part of the core functionality of the game. After a system is added to the engine, its
         * update method will be called on every frame of the engine. When the system is removed from the engine,
         * the update method is no longer called.
         *
         * The aggregate of all systems in the engine is the functionality of the game, with the update
         * methods of those systems collectively constituting the engine update loop. Systems generally operate on
         * node lists - collections of nodes. Each node contains the components from an entity in the engine
         * that match the node.
         */
        class System
        {
                friend Engine;
            public:
                System(const int priority) : _priority(priority), previous(), next() {}
                System() : System(0) {}
                virtual ~System();

                int priority() const {
                    return this->_priority;
                }

                void priority(const int priority) {
                    this->_priority = priority;
                }

                bool operator==(const System& other) const {
                    return this->priority() == other.priority();
                }

                bool operator<(const System& other) const {
                    return this->priority() < other.priority();
                }
            protected:
                int _priority;
                virtual void addToEngine(Engine&) {}
                virtual void removeFromEngine(Engine&) {}
                virtual void update(const float) = 0;
            private:
                unique_ptr<System> previous;
                unique_ptr<System> next;
        };
    }
}
#endif // SYSTEM_H
