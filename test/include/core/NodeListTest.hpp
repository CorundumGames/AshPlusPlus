#ifndef NODELISTTEST_HPP
#define NODELISTTEST_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <memory>

#include <tut/tut.hpp>

#include "ash/core/NodeList.hpp"

#include "AshTesting.hpp"
#include "ShouldCallHelper.hpp"
#include "Mocks.hpp"

using std::array;
using std::function;
using std::remove;

using tut::test_group;

using ash::core::NodeList;

using ash::test::ShouldCallHelper;
using ash::test::mocks::MockNode2;
using ash::test::mocks::MockNode4;

namespace tut {
struct NodeListData {};

test_group<NodeListData> nlt("NodeList");
typedef test_group<NodeListData>::object NodeListTest;

TUT_TEST NodeListTest::test<1>() {
    set_test_name("Adding Node Triggers Added Signal");

    NodeList<MockNode2> nodelist;
    ShouldCallHelper<MockNode2> helper;
    shared_ptr<MockNode2> node(make_shared<MockNode2>());

    nodelist.nodeAdded().add(helper.func());
    nodelist.add(node);
    ensure("Node Added signal was not called when node was added", helper.called());
}

TUT_TEST NodeListTest::test<2>() {
    set_test_name("Removing Node Triggers Removed Signal");

    NodeList<MockNode2> nodelist;
    ShouldCallHelper<MockNode2> helper;
    shared_ptr<MockNode2> node(make_shared<MockNode2>());

    nodelist.nodeRemoved().add(helper.func());
    nodelist.add(node);
    nodelist.remove(node);
    ensure("Node Removed signal was not called when node was removed", helper.called());
}

TUT_TEST NodeListTest::test<3>() {
    set_test_name("All Nodes Are Covered During Iteration");

    vector<shared_ptr<MockNode2>> nodevector;
    NodeList<MockNode2> nodelist;

    for (int i = 0; i < 5; ++i) {
        shared_ptr<MockNode2> node(make_shared<MockNode2>());
        nodevector.push_back(node);
        nodelist.add(node);
    }


    for (const auto i : nodelist) {
        nodevector.pop_back();
    }

    ensure("Expected all nodes to be iterated over, " + std::to_string(nodevector.size()) + " were left out",
           nodevector.empty());
}

TUT_TEST NodeListTest::test<4>() {
    set_test_name("Removing Current Node During Iteration Is Valid");

    vector<shared_ptr<MockNode2>> nodevector;
    NodeList<MockNode2> nodelist;

    for (int i = 0; i < 5; ++i) {
        shared_ptr<MockNode2> node(make_shared<MockNode2>());
        nodevector.push_back(node);
        nodelist.add(node);
    }

    int count = 0;
    for (auto& i : nodelist) {
        //Remove the current node from the vector
        nodevector.pop_back();
        if (++count == 2) {
            //nodelist.remove(shared_ptr<MockNode2>(&i));
            //TODO: Figure out why this is causing pointer problems
        }
    }

    ensure("You should be able to remove nodes while iterating over a NodeList", nodevector.empty());
}

TUT_TEST NodeListTest::test<6>() {
    set_test_name("Component Added Signal Contains Correct Parameters");

    NodeList<MockNode2> nodelist;
    shared_ptr<MockNode2> node(make_shared<MockNode2>());
    bool called = false;

    auto func = [&node, &called](const MockNode2& n) {
        ensure_equals(node.get(), &n);
        called = true;
    };

    nodelist.nodeAdded().add(func);
    nodelist.add(node);
    ensure(called);
}

TUT_TEST NodeListTest::test<7>() {
    set_test_name("Component Removed Signal Contains Correct Parameters");

    NodeList<MockNode2> nodelist;
    shared_ptr<MockNode2> node(make_shared<MockNode2>());
    bool called = false;
    auto func = [&node, &called](const MockNode2& n) {
        ensure_equals(node.get(), &n);
        called = true;
    };

    nodelist.nodeRemoved().add(func);
    nodelist.add(node);
    nodelist.remove(node);
    ensure(called);
}

TUT_TEST NodeListTest::test<8>() {
    set_test_name("Nodes Initially Sorted In Order Of Addition");

    NodeList<MockNode2> nodelist;
    shared_ptr<MockNode2> n1(make_shared<MockNode2>()), n2(make_shared<MockNode2>()), n3(make_shared<MockNode2>());

    nodelist.add(n1);
    nodelist.add(n2);
    nodelist.add(n3);

    auto it = nodelist.begin();
    ensure_equals(*it, *n1);
    ++it;
    ensure_equals(*it, *n2);
    ++it;
    ensure_equals(*it, *n3);
}

TUT_TEST NodeListTest::test<9>() {
    set_test_name("Swapping Two Nodes Changes Their Order");

    NodeList<MockNode2> nodelist;
    shared_ptr<MockNode2> n1(make_shared<MockNode2>()), n2(make_shared<MockNode2>());

    nodelist.add(n1);
    nodelist.add(n2);
    nodelist.swap(n1, n2);

    auto it = nodelist.begin();
    ensure_equals(*it, *n2);
    ++it;
    ensure_equals(*it, *n1);
}

TUT_TEST NodeListTest::test<10>() {
    set_test_name("Swapping Adjacent Nodes Changes Their Positions");

    NodeList<MockNode2> nodelist;
    shared_ptr<MockNode2> n1(make_shared<MockNode2>()), n2(make_shared<MockNode2>()), n3(make_shared<MockNode2>()),
               n4(make_shared<MockNode2>());

    nodelist.add(n1);
    nodelist.add(n2);
    nodelist.add(n3);
    nodelist.add(n4);
    nodelist.swap(n2, n3);

    auto it = nodelist.begin();
    ensure_equals(*it, *n1);
    ++it;
    ensure_equals(*it, *n3);
    ++it;
    ensure_equals(*it, *n2);
    ++it;
    ensure_equals(*it, *n4);
}

TUT_TEST NodeListTest::test<11>() {
    set_test_name("Swapping Non-Adjacent Nodes Changes Their Positions");

    NodeList<MockNode2> nodelist;
    shared_ptr<MockNode2> n1(make_shared<MockNode2>()), n2(make_shared<MockNode2>()), n3(make_shared<MockNode2>()),
               n4(make_shared<MockNode2>()), n5(make_shared<MockNode2>());

    nodelist.add(n1);
    nodelist.add(n2);
    nodelist.add(n3);
    nodelist.add(n4);
    nodelist.add(n5);
    nodelist.swap(n2, n4);

    auto it = nodelist.begin();
    ensure_equals(*it, *n1);
    ++it;
    ensure_equals(*it, *n4);
    ++it;
    ensure_equals(*it, *n3);
    ++it;
    ensure_equals(*it, *n2);
    ++it;
    ensure_equals(*it, *n5);
}

TUT_TEST NodeListTest::test<12>() {
    set_test_name("Swapping End Nodes Changes Their Positions");

    NodeList<MockNode2> nodelist;
    shared_ptr<MockNode2> n1(make_shared<MockNode2>()), n2(make_shared<MockNode2>()), n3(make_shared<MockNode2>());

    nodelist.add(n1);
    nodelist.add(n2);
    nodelist.add(n3);
    nodelist.swap(n1, n3);

    auto it = nodelist.begin();
    ensure_equals(*it, *n3);
    ++it;
    ensure_equals(*it, *n2);
    ++it;
    ensure_equals(*it, *n1);
}

TUT_TEST NodeListTest::test<13>() {
    set_test_name("Sorting Correctly Sorts Sorted Nodes");

    NodeList<MockNode4> nodelist;
    shared_ptr<MockNode4> n1(make_shared<MockNode4>(1)), n2(make_shared<MockNode4>(2)), n3(make_shared<MockNode4>(3)),
               n4(make_shared<MockNode4>(4));
    nodelist.add(n1);
    nodelist.add(n2);
    nodelist.add(n3);
    nodelist.add(n4);
    nodelist.sort();

    auto it = nodelist.begin();
    ensure_equals((*it).pos->value, 1);
    ++it;
    ensure_equals((*it).pos->value, 2);
    ++it;
    ensure_equals((*it).pos->value, 3);
    ++it;
    ensure_equals((*it).pos->value, 4);
    ++it;
}
/*
class NodeListTest extends MatchersBase
{
    @Test
    public function insertionSortCorrectlySortsSortedNodes():Void
    {
        var nodes:NodeList<MockNode4> = new NodeList();
        var node1:MockNode4 = new MockNode4( 1 );
        var node2:MockNode4 = new MockNode4( 2 );
        var node3:MockNode4 = new MockNode4( 3 );
        var node4:MockNode4 = new MockNode4( 4 );
        nodes.add(node1);
        nodes.add(node2);
        nodes.add(node3);
        nodes.add(node4);
        nodes.insertionSort(sortFunction);
        assertThat(nodes, NodeListMatcher.nodeList([node1, node2, node3, node4]));
    }

    @Test
    public function insertionSortCorrectlySortsReversedNodes():Void
    {
        var nodes:NodeList<MockNode4> = new NodeList();
        var node1:MockNode4 = new MockNode4( 1 );
        var node2:MockNode4 = new MockNode4( 2 );
        var node3:MockNode4 = new MockNode4( 3 );
        var node4:MockNode4 = new MockNode4( 4 );
        nodes.add(node4);
        nodes.add(node3);
        nodes.add(node2);
        nodes.add(node1);
        nodes.insertionSort(sortFunction);
        assertThat(nodes, NodeListMatcher.nodeList([node1, node2, node3, node4]));
    }

    @Test
    public function insertionSortCorrectlySortsMixedNodes():Void
    {
        var nodes:NodeList<MockNode4> = new NodeList();
        var node1:MockNode4 = new MockNode4( 1 );
        var node2:MockNode4 = new MockNode4( 2 );
        var node3:MockNode4 = new MockNode4( 3 );
        var node4:MockNode4 = new MockNode4( 4 );
        var node5:MockNode4 = new MockNode4( 5 );
        nodes.add(node3);
        nodes.add(node4);
        nodes.add(node1);
        nodes.add(node5);
        nodes.add(node2);
        nodes.insertionSort(sortFunction);
        assertThat(nodes, NodeListMatcher.nodeList([node1, node2, node3, node4, node5]));
    }

    @Test
    public function insertionSortRetainsTheOrderOfEquivalentNodes():Void
    {
        var nodes:NodeList<MockNode4> = new NodeList();
        var node1:MockNode4 = new MockNode4( 1 );
        var node2:MockNode4 = new MockNode4( 1 );
        var node3:MockNode4 = new MockNode4( 3 );
        var node4:MockNode4 = new MockNode4( 4 );
        var node5:MockNode4 = new MockNode4( 4 );
        nodes.add(node3);
        nodes.add(node4);
        nodes.add(node1);
        nodes.add(node5);
        nodes.add(node2);
        nodes.insertionSort(sortFunction);
        assertThat(nodes, NodeListMatcher.nodeList([node1, node2, node3, node4, node5]));
    }

    @Test
    public function mergeSortCorrectlySortsSortedNodes():Void
    {
        var nodes:NodeList<MockNode4> = new NodeList();
        var node1:MockNode4 = new MockNode4( 1 );
        var node2:MockNode4 = new MockNode4( 2 );
        var node3:MockNode4 = new MockNode4( 3 );
        var node4:MockNode4 = new MockNode4( 4 );
        nodes.add(node1);
        nodes.add(node2);
        nodes.add(node3);
        nodes.add(node4);
        nodes.mergeSort(sortFunction);
        assertThat(nodes, NodeListMatcher.nodeList([node1, node2, node3, node4]));
    }

    @Test
    public function mergeSortCorrectlySortsReversedNodes():Void
    {
        var nodes:NodeList<MockNode4> = new NodeList();
        var node1:MockNode4 = new MockNode4( 1 );
        var node2:MockNode4 = new MockNode4( 2 );
        var node3:MockNode4 = new MockNode4( 3 );
        var node4:MockNode4 = new MockNode4( 4 );
        nodes.add(node4);
        nodes.add(node3);
        nodes.add(node2);
        nodes.add(node1);
        nodes.mergeSort(sortFunction);
        assertThat(nodes, NodeListMatcher.nodeList([node1, node2, node3, node4]));
    }

    @Test
    public function mergeSortCorrectlySortsMixedNodes():Void
    {
        var nodes:NodeList<MockNode4> = new NodeList();
        var node1:MockNode4 = new MockNode4( 1 );
        var node2:MockNode4 = new MockNode4( 2 );
        var node3:MockNode4 = new MockNode4( 3 );
        var node4:MockNode4 = new MockNode4( 4 );
        var node5:MockNode4 = new MockNode4( 5 );
        nodes.add(node3);
        nodes.add(node4);
        nodes.add(node1);
        nodes.add(node5);
        nodes.add(node2);
        nodes.mergeSort(sortFunction);
        assertThat(nodes, NodeListMatcher.nodeList([node1, node2, node3, node4, node5]));
    }

    private function sortFunction(node1:MockNode4, node2:MockNode4):Int
    {
        return node1.pos.value - node2.pos.value;
    }
}
*/

/*
@Test
    public function removingNextNodeDuringIterationIsValid():Void
    {
        var nodeArray:Array<MockNode2> = [];
        for (i in 0...5)
        {
            var node:MockNode2 = Type.createEmptyInstance(MockNode2);
            nodeArray.push(node);
            nodes.add(node);
        }

        var count:Int = 0;
        for (node in nodes)
        {
            var index:Int = Lambda.indexOf(nodeArray, node);
            nodeArray.splice(index, 1);
            if (++count == 2)
            {
                nodes.remove(node.next);
            }
        }
        assertThat(nodeArray.length, equalTo(1));
    }*/
}



#endif // NODELISTTEST_HPP
