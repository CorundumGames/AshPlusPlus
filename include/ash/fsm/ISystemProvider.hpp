#ifndef ISYSTEMPROVIDER_H
#define ISYSTEMPROVIDER_H


namespace ash {
namespace fsm {
template<class C, class I>
class ISystemProvider
{
    public:
        virtual C getSystem() = 0;
        virtual I const& identifier() const = 0;
        virtual int priority() const = 0;
        virtual void priority(const int) = 0;
};
}
}

#endif // ISYSTEMPROVIDER_H
