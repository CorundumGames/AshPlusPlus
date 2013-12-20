#ifndef ITICKPROVIDER_H
#define ITICKPROVIDER_H

#include <functional>

using std::function;

namespace ash {
    namespace tick {
        class ITickProvider
        {
            public:
                virtual void add(const function<void(float)>&) = 0;
                virtual void remove(const function<void(float)>&) = 0;
                virtual void start() = 0;
                virtual void stop() = 0;
                virtual bool playing() const = 0;
            protected:
                using Listener = function<void(float)>;
        };

    }
}
#endif // ITICKPROVIDER_H
