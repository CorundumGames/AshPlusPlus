#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>
#include <utility>

#include "Declarations.hpp"
#include "ash/core/Engine.hpp"

using std::unique_ptr;


namespace ash {
namespace core {
using namespace std::rel_ops;
/**
 * The base class for a system.
 *
 * A system is part of the core functionality of the game. After a system is added to the engine, its update method will
 * be called on every frame of the engine. When the system is removed from the engine, the update method is no longer
 * called.
 *
 * The aggregate of all systems in the engine is the functionality of the game, with the update methods of those systems
 * collectively constituting the engine update loop. Systems generally operate on node lists - collections of nodes.
 * Each node contains the components from an entity in the engine that match the node.
 */
class System
{

    public:
        System(const int priority);
        System();
        virtual ~System();

        int priority() const;

        void priority(const int priority);

        bool operator==(const System& other) const;

        bool operator<(const System& other) const;
    protected:
        int _priority;

        /**
         * Called just after the system is added to the engine, before any calls to the update method. Override this
         * method to add your own functionality.
         *
         * @param engine The engine the system was added to.
         */
        virtual void addToEngine(const shared_ptr<Engine> engine);

        /**
         * Called just after the system is removed from the engine, after all calls to the update method. Override this
         * method to add your own functionality.
         *
         * @param engine The engine the system was removed from.
         */
        virtual void removeFromEngine(const shared_ptr<Engine> engine);

        /**
         * After the system is added to the engine, this method is called every frame until the system is removed from
         * the engine. Override this method to add your own functionality.
         *
         * If you need to perform an action outside of the update loop (e.g. you need to change the systems in the
         * engine and you don't want to do it while they're updating) add a listener to the engine's updateComplete
         * signal to be notified when the update loop completes.
         *
         * @param time The duration, in seconds, of the frame.
         */
        virtual void update(const double time) = 0;
    private:
        friend Engine;
};
}
}
#endif // SYSTEM_H
