#ifndef ENTITYTEST_HPP_INCLUDED
#define ENTITYTEST_HPP_INCLUDED

#include <algorithm>
#include <iostream>
#include <string>
#include <memory>

#include <tut/tut.hpp>

#include "ash/core/Entity.hpp"

#include "AshTesting.hpp"
#include "ShouldCallHelper.hpp"
#include "Mocks.hpp"

using std::make_shared;
using std::string;
using std::find;

using ash::core::Entity;
using ash::test::mocks::MockComponent;
using ash::test::mocks::MockComponent2;
using ash::test::mocks::MockComponentExtended;
using ash::test::ShouldCallHelper;
using ash::test::ShouldCallHelper2;

namespace tut {
struct EntityData {};
test_group<EntityData> _entity_test("Entity");
typedef test_group<EntityData>::object EntityTest;

TUT_TEST EntityTest::test<1>() {
    set_test_name("Add Returns Reference To Entity");

    shared_ptr<MockComponent> component(make_shared<MockComponent>());
    shared_ptr<Entity> entity(make_shared<Entity>());

    ensure_equals(&(entity->add(component)), entity.get());
}

TUT_TEST EntityTest::test<2>() {
    set_test_name("Can Store And Retrieve Component");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent> component(make_shared<MockComponent>());

    entity->add(component);
    ensure_equals(entity->get<MockComponent>(), component);
}

TUT_TEST EntityTest::test<3>() {
    set_test_name("Can Store And Retrieve Multiple Components");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent> c1(make_shared<MockComponent>());
    shared_ptr<MockComponent2> c2(make_shared<MockComponent2>());

    entity->add(c1);
    entity->add(c2);

    ensure_equals(entity->get<MockComponent>(), c1);
    ensure_equals(entity->get<MockComponent2>(), c2);
}

TUT_TEST EntityTest::test<4>() {
    set_test_name("Can Replace Component");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent> c1(make_shared<MockComponent>()), c2(make_shared<MockComponent>());

    entity->add(c1);
    entity->add(c2);

    ensure_equals(entity->get<MockComponent>(), c2);
}

TUT_TEST EntityTest::test<5>() {
    set_test_name("Can Store Base And Extended Components");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent> c1(make_shared<MockComponent>());
    shared_ptr<MockComponentExtended> c2(make_shared<MockComponentExtended>());

    entity->add(c1);
    entity->add<MockComponentExtended>(c2);

    ensure_equals(entity->get<MockComponent>(), c1);
    ensure_equals(entity->get<MockComponentExtended>(), c2);
}

TUT_TEST EntityTest::test<6>() {
    set_test_name("Can Store Extended Component As Base Type");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponentExtended> component(make_shared<MockComponentExtended>());

    entity->add<MockComponent>(component);
    ensure_equals(entity->get<MockComponent>(), component);
}

TUT_TEST EntityTest::test<7>() {
    set_test_name("get() Returns Null If Component Doesn't Exist");

    shared_ptr<Entity> entity(make_shared<Entity>());

    ensure_equals(entity->get<MockComponent>().get(), static_cast<MockComponent*>(NULL));
}

TUT_TEST EntityTest::test<8>() {
    set_test_name("Will Retrieve All Components");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent> c1(make_shared<MockComponent>());
    shared_ptr<MockComponent2> c2(make_shared<MockComponent2>());

    entity->add(c1);
    entity->add(c2);

    auto all = entity->getAll();
    ensure_equals(all.size(), 2);

    ensure_not(find(all.begin(), all.end(), c1) == all.end());
    ensure_not(find(all.begin(), all.end(), c2) == all.end());
}

TUT_TEST EntityTest::test<9>() {
    set_test_name("has() Is False If Component Type Isn't Present");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent2> component(make_shared<MockComponent2>());

    entity->add(component);
    ensure_not(entity->has<MockComponent>());
}

TUT_TEST EntityTest::test<10>() {
    set_test_name("has() is True If Component Type Is Present");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent> component(make_shared<MockComponent>());

    entity->add(component);
    ensure(entity->has<MockComponent>());
}

TUT_TEST EntityTest::test<11>() {
    set_test_name("Can Remove Component");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent> component(make_shared<MockComponent>());

    entity->add(component);
    entity->remove<MockComponent>();

    ensure_not(entity->has<MockComponent>());
}

TUT_TEST EntityTest::test<12>() {
    set_test_name("Storing Component Triggers Added Signal");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent> component(make_shared<MockComponent>());
    ShouldCallHelper2<Entity, type_index> helper;

    entity->componentAdded().add(helper.func());
    entity->add(component);

    ensure(helper.called());
}

TUT_TEST EntityTest::test<13>() {
    set_test_name("Removing Component Triggers Removed Signal");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent> component(make_shared<MockComponent>());
    ShouldCallHelper2<Entity, type_index> helper;

    entity->componentRemoved().add(helper.func());
    entity->add(component);
    entity->remove<MockComponent>();

    ensure(helper.called());
}

TUT_TEST EntityTest::test<14>() {
    set_test_name("Component Added Signal Contains The Correct Parameters");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent> component(make_shared<MockComponent>());

    entity->componentAdded().add([&entity](const Entity& e, const type_index& t) {
        ensure_equals(&e, entity.get());
        ensure_equals(t.hash_code(), type_index(typeid(MockComponent)).hash_code());
    });
    entity->add(component);
}

TUT_TEST EntityTest::test<15>() {
    set_test_name("Component Removed Signal Contains The Correct Parameters");

    shared_ptr<Entity> entity(make_shared<Entity>());
    shared_ptr<MockComponent> component(make_shared<MockComponent>());

    entity->componentRemoved().add([&entity](const Entity& e, const type_index& t) {
        ensure_equals(&e, entity.get());
        ensure_equals(t.hash_code(), type_index(typeid(MockComponent)).hash_code());
    });
    entity->add(component);
    entity->remove<MockComponent>();
}

TUT_TEST EntityTest::test<16>() {
    set_test_name("Entity Has Default Name");

    Entity entity;
    ensure_not(entity.name().empty());

}

TUT_TEST EntityTest::test<17>() {
    set_test_name("Entity Name Is Stored And Returned");

    string name = "anything";
    shared_ptr<Entity> entity(make_shared<Entity>(name));

    ensure_equals(entity->name(), name);
}

TUT_TEST EntityTest::test<18>() {
    set_test_name("Entity Name Can Be Changed");

    Entity entity("anything");
    entity.name("other");

    ensure_equals(entity.name(), "other");
}

TUT_TEST EntityTest::test<19>() {
    set_test_name("Changing Entity Name Dispatches Signal");

    string name1 = "anything", name2 = "other";
    shared_ptr<Entity> entity(make_shared<Entity>(name1));
    shared_ptr<MockComponent> component;
    ShouldCallHelper2<Entity, string> helper([&entity, &name1, &name2](const Entity& e, const string& old) {
        ensure_equals(entity.get(), &e);
        ensure_equals(entity->name(), name2);
        ensure_equals(old, name1);
    });

    entity->nameChanged().add(helper.func());
    entity->name(name2);
    ensure(helper.called());
}
}

#endif // ENTITYTEST_HPP_INCLUDED
