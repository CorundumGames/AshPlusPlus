#ifndef SIGNAL_H
#define SIGNAL_H

#include <list>
#include <memory>
#include <functional>

#include "Declarations.h"


using std::function;
using std::list;

namespace ash {
    namespace signals {
        template<typename...Types>
        class Signal
        {
                using Listener = function<void(Types...)>;
            public:
                Signal() : _listeners(), _dispatching(false) {}
                virtual ~Signal() {}
                void add(const Listener& listener) {
                    this->_listeners.push_back(Node(listener, false));
                }
                void addOnce(const Listener& listener) {
                    this->_listeners.push_back(Node(listener, true));
                }
                void remove(const Listener& listener) {
                    this->_listeners.remove(Node(listener, false));
                }
                void removeAll() {
                    this->_listeners.clear();
                }
                int numListeners() const {
                    return this->_listeners.size();
                }
                void dispatch(const Types&...args) {
                    this->_dispatching = true;
                    for (Node i : this->_listeners) {
                        i(args...);
                    }

                    this->_listeners.remove_if([](const Node& node) {
                        // Remove every node marked to be removed after one use...
                        return node.once();
                    });
                    this->_dispatching = false;
                }

            protected:
            private:

                class Node {
                    public:
                        Node(const Listener& listener, const bool once) {
                            this->_listener = listener;
                            this->_once = once;
                        }
                        bool once() const {
                            return this->_once;
                        }
                        Listener& listener() const {
                            return this->_listener;
                        }
                        void operator()(Types...args) {
                            this->_listener(args...);
                        }
                        bool operator==(const Node& other) {
                            return &this->_listener == &other._listener;
                        }
                    private:
                        Listener _listener;
                        bool _once;
                };

                list<Node> _listeners;
                bool _dispatching;
        };


    }
}

#endif // SIGNAL_H
