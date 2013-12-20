#ifndef ITICKPROVIDER_H
#define ITICKPROVIDER_H

#include <functional>

using std::function;

namespace ash {
namespace tick {
/**
 * The interface for a tick provider. A tick provider dispatches a regular update tick
 * to act as the heartbeat for the engine. It has methods to start and stop the tick and
 * to add and remove listeners for the tick.
 */
class ITickProvider
{
    public:

        virtual void add(const function<void(float)>&) = 0;
        virtual void remove(const function<void(float)>&) = 0;

        /**
         * Starts ticking, and executing queued listeners every so often in the order they were added.
         */
        virtual void start() = 0;

        /**
         * Stops this ITickProvider from ticking.  This tick provider will continue to execute all of the listeners it
         * has waiting.  It is safe to call this within a listener.
         */
        virtual void stop() = 0;

        /**
         * Returns true if this ITickProvider is running.  If stop() was called, may return false even when this tick
         * provider's listeners are being called for the last time.
         */
        virtual bool playing() const = 0;
    protected:
        virtual void dispatch_tick() = 0;
        using Listener = function<void(float)>;
};

}
}
#endif // ITICKPROVIDER_H
