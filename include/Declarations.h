#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED

namespace ash {
    namespace core {
        class Component;
        class System;
        class Engine;
        class Entity;
        class Node;
        class IFamily;
    }

    namespace fsm {
        template<class C, class I = C> class IComponentProvider;
        template<class C> class ComponentInstanceProvider;
        template<class C> class ComponentSingletonProvider;
        template<class C> class ComponentTypeProvider;
        template<class C> class DynamicComponentProvider;
        template<class C> class StateComponentMapping;
        template<class C, class I = C> class ISystemProvider;
        template<class C, class I = C> class AbstractSystemProvider;
        template<class C> class SystemInstanceProvider;
        template<class C> class SystemSingletonProvider;
        template<class C> class DynamicSystemProvider;
        template<class S> class StateSystemMapping;
        class EntityState;
        class EngineState;
        class EngineStateMachine;

    }

    namespace signals {
        template<typename...Types> class Signal;
        typedef Signal<> SignalBase;
        typedef Signal<> SignalAny;
        typedef Signal<> Signal0;
        template<class T> using Signal1 = Signal<T>;
        template<class T, class U> using Signal2 = Signal<T, U>;
        template<class T, class U, class V> using Signal3 = Signal<T, U, V>;
    }

    namespace tick {
        class ITickProvider;
        class FixedTickProvider;
        // FrameTickProvider is absent; makes no sense outside of Flash, where Ash originally came from
    }
}




#endif // DECLARATIONS_H_INCLUDED
