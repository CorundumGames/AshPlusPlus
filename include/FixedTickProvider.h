#ifndef FIXEDTICKPROVIDER_H
#define FIXEDTICKPROVIDER_H

#include "Declarations.h"
#include "ITickProvider.h"
#include "Signal.h"

using ash::signals::Signal1;

namespace ash {
    namespace tick {
        class FixedTickProvider : public ITickProvider
        {
            public:
                FixedTickProvider() : _playing(false), _signal(), _frame_time(0.0) {}
                virtual ~FixedTickProvider();
                void add(const Listener&);
                void remove(const Listener&);
                void start();
                void stop();
                bool playing() const;
                double time_adjustment() const;
                void time_adjustment(const double);
            protected:
            private:
                bool _playing;
                double _frame_time;
                double _time_adjustment;
                Signal1<double> _signal;
        };
    }
}

#endif // FIXEDTICKPROVIDER_H
