#ifndef SHOULDCALLHELPER_HPP
#define SHOULDCALLHELPER_HPP

#include <functional>

using std::function;
using std::bind;

using namespace std::placeholders;

namespace ash {
namespace test {
template<class T>

class ShouldCallHelper
{
    using Callback = function<void(const T&)>;
    public:
        ShouldCallHelper(const Callback& callback) : _callback(callback) {}
        ShouldCallHelper() : ShouldCallHelper([](const T&){}) {}
        void operator()(const T& arg) {
            this->_callback(arg);
            _called = true;
        }
        bool called() const {
            return this->_called;
        }
        Callback func() {
            return Callback(bind(&ShouldCallHelper::operator(), this, _1));
        }
    private:
        Callback _callback;
        bool _called;
};

template<class T, class U>
class ShouldCallHelper2
{
    using Callback = function<void(const T&, const U&)>;
    public:
        ShouldCallHelper2(const Callback& callback) : _callback(callback) {}
        ShouldCallHelper2() : ShouldCallHelper2([](const T&, const U&){}) {}
        void operator()(const T& arg1, const U& arg2) {
            this->_callback(arg1, arg2);
            _called = true;
        }
        bool called() const {
            return this->_called;
        }
        Callback func() {
            return Callback(bind(&ShouldCallHelper2::operator(), this, _1, _2));
        }
    private:
        Callback _callback;
        bool _called;
};
}
}

#endif // SHOULDCALLHELPER_HPP
