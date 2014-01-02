#ifndef MOCKS_HPP
#define MOCKS_HPP

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "ash/core/Node.hpp"
#include "ash/core/Component.hpp"
#include "ash/core/System.hpp"
#include "ash/core/Engine.hpp"

using std::shared_ptr;
using std::make_shared;
using std::string;

using ash::core::Engine;
using ash::core::System;
using ash::core::Component;
using ash::core::Node;

namespace ash {
namespace test {
namespace mocks {
struct Point;
struct Matrix;
struct MockComponent;
struct MockComponent2;
struct MockComponentExtended;
struct MockNode;
struct MockNode2;
struct MockNode3;
struct MockNode4;
class MockSystem;
class EmptySystem;
class EmptySystem2;

struct Point : public Component {};

struct Matrix : public Component {};

struct MockComponent : public Component
{
    int value;
    MockComponent(const int value = 0) : value(value) {}

    bool operator==(const MockComponent& other) const {
        return this->value == other.value;
    }

    bool operator!=(const MockComponent& other) const {
        return !this->operator==(other);
    }

    bool operator<(const MockComponent& other) const {
        return this->value < other.value;
    }
};

struct MockComponent2 : public Component {
    string value;
};

struct MockComponentExtended: public MockComponent {
    int other;
    MockComponentExtended() : MockComponent() {}
};

struct MockNode : public Node {
    shared_ptr<Point> point;

    void reset() override {
        Node::reset();
        this->point = nullptr;
    }
};

struct MockNode2 : public Node {
    shared_ptr<Point> point;
    shared_ptr<Matrix> matrix;

    MockNode2() : Node(), point(make_shared<Point>(Point())), matrix(make_shared<Matrix>(Matrix())) {}


    void reset() override {
        Node::reset();
        this->point = nullptr;
        this->matrix = nullptr;
    }

    bool operator==(const MockNode2& other) const {
        return (this->entity == other.entity) && (this->point == other.point) && (this->matrix == other.matrix);
    }

    bool operator!=(const MockNode2& other) const {
        return !this->operator==(other);
    }
};

std::ostream& operator<<(std::ostream& os, const MockNode2& node) {
    return (os << &node);
}

std::ostream& operator<<(std::ostream& os, const MockComponent& node) {
    return (os << &node);
}

struct MockNode3 : public Node
{
    shared_ptr<Matrix> matrix;
    void reset() override {
        Node::reset();
        this->matrix = nullptr;
    }
};

struct MockNode4 : public Node
{
    shared_ptr<MockComponent> pos;

    MockNode4(const int value = 0) : pos(new MockComponent(value)) {}
    void reset() override {
        Node::reset();
        this->pos = nullptr;
    }

    bool operator==(const MockNode4& other) const {
        if (this->pos == nullptr && other.pos == nullptr) return true;
        // If both this node and the other node have null components...
        if ((this->pos == nullptr) != (other.pos == nullptr)) return false;
        // If this node or the other have null components, but not both...
        return *(this->pos) == *(other.pos);
    }
    bool operator<(const MockNode4& other) const {
        if (this->pos == nullptr && other.pos == nullptr) return false;
        if (this->pos == nullptr && other.pos != nullptr) return true;
        if (this->pos != nullptr && other.pos == nullptr) return false;
        return *(this->pos) < *(other.pos);
    }
};

class MockSystem : public System {
    public:
        MockSystem() : System() {}

        void addToEngine(Engine& engine) override {
        }

        void removeFromEngine(Engine& engine) override {
        }

        void update(const double time) override {
        }
};

class EmptySystem : public System {
    public:
        void update(const double time) {}
};

class EmptySystem2: public System {
    public:
        string value;
        void update(const double time) {}
};

/*
class MockSystem extends System
{
    private var tests:SystemTest;

    public function new(tests:SystemTest)
    {
        super();
        this.tests = tests;
    }

    override public function addToEngine(engine:Engine):Void
    {
        if (tests.callBack != null)
            tests.callBack(this, "added", engine);
    }

    override public function removeFromEngine(engine:Engine):Void
    {
        if (tests.callBack != null)
            tests.callBack(this, "removed", engine);
    }

    override public function update(time:Float):Void
    {
        if (tests.callBack != null)
            tests.callBack(this, "update", time);
    }
}
*/
}
}
}

#endif // MOCKS_HPP
