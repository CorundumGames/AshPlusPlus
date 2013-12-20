#ifndef FIXEDTICKPROVIDER_H
#define FIXEDTICKPROVIDER_H

#include <atomic>
#include <chrono>

#include "Declarations.h"
#include "ITickProvider.h"
#include "Signal.h"

using std::atomic;
using std::chrono::milliseconds;

using ash::signals::Signal1;

namespace ash {
namespace tick {

/**
 * Uses the enter frame event to provide a frame tick with a fixed frame duration. This tick ignores the length of
 * the frame and dispatches the same time period for each tick.
 */
class FixedTickProvider : public ITickProvider
{
    public:
        FixedTickProvider();
        FixedTickProvider(const double frameTime);
        virtual ~FixedTickProvider();
        void add(const Listener&);
        void remove(const Listener&);
        void start();
        void stop();
        bool playing() const;
        double time_adjustment() const;
        void time_adjustment(const double);
    protected:
        void dispatch_tick();
    private:
        atomic<bool> _playing;
        milliseconds _frame_time;
        atomic<double> _time_adjustment;
        Signal1<double> _signal;


};
}
}

#endif // FIXEDTICKPROVIDER_H
