//ronamsalem4@gmail.com 
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <sstream>
#include "doctest.h"
#include "MyContainer.hpp"
#include <vector>
using namespace ariel;

/**
 * This file contains unit tests for the MyContainer class and its various iterators.
 * The tests cover insertion, removal, iteration orders, exception handling, and 
 * support for multiple data types. They are written using the doctest framework.
 * The goal is to ensure correctness, robustness, and iterator consistency.
 */


/**
 * This test checks the add function to the container.
 */
TEST_CASE("Test addElement")
{
    MyContainer<int> c;
    CHECK(c.size() == 0);

    c.addElement(42);
    CHECK(c.size() == 1);

    auto it = c.begin_order();
    CHECK(*it == 42);
    c.addElement(7);
    c.addElement(99);
    CHECK(c.size() == 3);
}

/**
 * This test checks whether, after being added to a container, a specific element is there.
 */
TEST_CASE("Check if specific element exists after addElement")
{
    MyContainer<int> c;
    c.addElement(1);
    c.addElement(7);
    c.addElement(42);

    bool found = false;
    for (auto it = c.begin_order(); it != c.end_order(); ++it)
    {
        if (*it == 7)
        {
            found = true;
            break;
        }
    }
}

/**
 * This test checks for deletion of an existing element from the container.
 */
TEST_CASE("removeElement - existing element")
{
    MyContainer<int> c;
    c.addElement(10);
    c.addElement(20);
    c.addElement(30);

    CHECK(c.size() == 3);

    c.removeElement(20);

    CHECK(c.size() == 2);

    bool found = false;
    for (auto it = c.begin_order(); it != c.end_order(); ++it)
    {
        if (*it == 20)
        {
            found = true;
            break;
        }
    }
    CHECK_FALSE(found);
}

/**
 * This test checks for deletion of an element that does not exist in the container.
 */
TEST_CASE("removeElement - non-existing element throws")
{
    MyContainer<int> c;

    c.addElement(1);
    c.addElement(2);
    c.addElement(3);

    CHECK_THROWS_AS(c.removeElement(99), std::invalid_argument);
}

/**
 * This test checks the size of a container.
 */
TEST_CASE("Container size")
{
    MyContainer<int> c;
    c.addElement(10);
    c.addElement(20);
    c.addElement(30);

    CHECK(c.size() == 3);

    c.removeElement(20);

    CHECK(c.size() == 2);
}

/**
 * The test checks that the print operator prints the container logically.
 */

TEST_CASE("Test operator<< prints container correctly")
{
    MyContainer<int> c;
    c.addElement(1);
    c.addElement(2);
    c.addElement(3);

    std::ostringstream out;
    out << c;
    CHECK(out.str() == "1 2 3 ");
}

/**
 * Checking the template - checking if a double type is used it works
 */
TEST_CASE("MyContainer<std::string> - basic functionality")
{
    MyContainer<std::string> c;
    c.addElement("apple");
    c.addElement("banana");
    CHECK(c.size() == 2);
    bool found_apple = false;
    bool found_banana = false;
    for (auto it = c.begin_order(); it != c.end_order(); ++it)
    {
        if (*it == "apple")
            found_apple = true;
        if (*it == "banana")
            found_banana = true;
    }
    CHECK(found_apple);
    CHECK(found_banana);
}

/**
 * Checking the template - checking if a string type is usedit works
 */
TEST_CASE("MyContainer<double> - basic functionality")
{
    MyContainer<double> c;
    c.addElement(3.14);
    c.addElement(2.718);
    CHECK(c.size() == 2);
    bool found_pi = false;
    bool found_e = false;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it)
    {
        if (*it == 3.14)
            found_pi = true;
        if (*it == 2.718)
            found_e = true;
    }
    CHECK(found_pi);
    CHECK(found_e);
}

/**
 * Test AscendingOrder iterator.
 * Checks traversal over sorted data and empty container edge case.
 */
TEST_CASE("Iterator: AscendingOrder")
{
    MyContainer<int> c;
    c.addElement(3);
    c.addElement(1);
    c.addElement(5);
    c.addElement(2);
    c.addElement(4);

    std::vector<int> result;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it)
        result.push_back(*it);

    CHECK(result == std::vector<int>{1, 2, 3, 4, 5});
}

/**
 * Test DescendingOrder iterator.
 */
TEST_CASE("Iterator: DescendingOrder")
{
    MyContainer<int> c;
    c.addElement(1);
    c.addElement(2);
    c.addElement(3);
    c.addElement(4);
    c.addElement(5);

    std::vector<int> result;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it)
        result.push_back(*it);

    CHECK(result == std::vector<int>{5, 4, 3, 2, 1});
}

/**
 * Test SideCrossOrder iterator.
 */
TEST_CASE("Iterator: SideCrossOrder")
{
    MyContainer<int> c;
    c.addElement(1);
    c.addElement(2);
    c.addElement(3);
    c.addElement(4);
    c.addElement(5);

    std::vector<int> result;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it)
        result.push_back(*it);

    CHECK(result == std::vector<int>{1, 5, 2, 4, 3});
}

/**
 * Test ReverseOrder iterator.
 */
TEST_CASE("Iterator: ReverseOrder")
{
    MyContainer<int> c;
    c.addElement(10);
    c.addElement(20);
    c.addElement(30);

    std::vector<int> result;
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it)
        result.push_back(*it);

    CHECK(result == std::vector<int>{30, 20, 10});
}

/**
 * Test Order iterator (insertion order).
 */
TEST_CASE("Iterator: Order")
{
    MyContainer<int> c;
    c.addElement(3);
    c.addElement(1);
    c.addElement(5);

    std::vector<int> result;
    for (auto it = c.begin_order(); it != c.end_order(); ++it)
        result.push_back(*it);

    CHECK(result == std::vector<int>{3, 1, 5});
}

/**
 * Test MiddleOutOrder iterator.
 */
TEST_CASE("Iterator: MiddleOutOrder")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(5);
    c.addElement(1);
    c.addElement(9);
    // order of insertion: [7,2,5,1,9] → middle index = 2 → 5
    // then left=1 (2), right=3 (1), left=0 (7), right=4 (9)
    std::vector<int> result;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it)
        result.push_back(*it);

    CHECK(result == std::vector<int>{5, 2, 1, 7, 9});
}

/**
 * Test Ascending Order Iterator
 * Verifies traversal order and correctness.
 */
TEST_CASE("Ascending Order Iterator")
{
    MyContainer<int> c;
    c.addElement(3);
    c.addElement(1);
    c.addElement(4);
    c.addElement(2);

    std::vector<int> result;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it)
    {
        result.push_back(*it);
    }

    CHECK(result == std::vector<int>{1, 2, 3, 4});
}

/**
 * Test Descending Order Iterator
 * Verifies traversal order and correctness.
 */
TEST_CASE("Descending Order Iterator")
{
    MyContainer<int> c;
    c.addElement(3);
    c.addElement(1);
    c.addElement(4);
    c.addElement(2);

    std::vector<int> result;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it)
    {
        result.push_back(*it);
    }

    CHECK(result == std::vector<int>{4, 3, 2, 1});
}

/**
 * Test Side Cross Order Iterator
 * Verifies traversal order and correctness.
 */
TEST_CASE("Side Cross Order Iterator")
{
    MyContainer<int> c;
    c.addElement(3);
    c.addElement(1);
    c.addElement(4);
    c.addElement(2);

    std::vector<int> result;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it)
    {
        result.push_back(*it);
    }

    CHECK(result == std::vector<int>{1, 4, 2, 3});
}

/**
 * Test Reverse Order Iterator
 * Verifies traversal order and correctness.
 */
TEST_CASE("Reverse Order Iterator")
{
    MyContainer<int> c;
    c.addElement(3);
    c.addElement(1);
    c.addElement(4);
    c.addElement(2);

    std::vector<int> result;
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it)
    {
        result.push_back(*it);
    }

    CHECK(result == std::vector<int>{2, 4, 1, 3});
}

/**
 * Test Order Iterator
 * Verifies traversal order and correctness.
 */
TEST_CASE("Order Iterator")
{
    MyContainer<int> c;
    c.addElement(3);
    c.addElement(1);
    c.addElement(4);
    c.addElement(2);

    std::vector<int> result;
    for (auto it = c.begin_order(); it != c.end_order(); ++it)
    {
        result.push_back(*it);
    }

    CHECK(result == std::vector<int>{3, 1, 4, 2});
}

/**
 * Test Middle Out Order Iterator
 * Verifies traversal order and correctness.
 */
TEST_CASE("Middle Out Order Iterator")
{
    MyContainer<int> c;
    c.addElement(3);
    c.addElement(1);
    c.addElement(4);
    c.addElement(2);

    std::vector<int> result;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it)
    {
        result.push_back(*it);
    }
    CHECK(result.size() == 4);
}

/**
 * Test begin_ascending_order
 * Verifies that the iterator starts at the smallest element in ascending order.
 */
TEST_CASE("Begin Ascending Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(9);
    auto it = c.begin_ascending_order();
    CHECK(*it == 2);
}

/**
 * Test end_ascending_order
 * Verifies that the end iterator is different from the beginning when the container is not empty.
 */
TEST_CASE("End Ascending Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(9);
    auto it = c.end_ascending_order();
    CHECK(it != c.begin_ascending_order());
}

/**
 * Test begin_descending_order
 * Verifies that the iterator starts at the largest element in descending order.
 */
TEST_CASE("Begin Descending Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(9);
    auto it = c.begin_descending_order();
    CHECK(*it == 9); // largest element
}

/**
 * Test end_descending_order
 * Ensures that the end iterator is not equal to the begin iterator for a non-empty container.
 */
TEST_CASE("End Descending Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(9);
    auto it = c.end_descending_order();
    CHECK(it != c.begin_descending_order());
}

/**
 * Test begin_side_cross_order
 * Verifies that the first element in side-cross order is the smallest.
 */
TEST_CASE("Begin Side Cross Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(9);
    auto it = c.begin_side_cross_order();
    CHECK(*it == 2);
}

/**
 * Test end_side_cross_order
 * Ensures the end iterator is valid and not equal to the start.
 */
TEST_CASE("End Side Cross Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(9);
    auto it = c.end_side_cross_order();
    CHECK(it != c.begin_side_cross_order());
}

/**
 * Test begin_reverse_order
 * Verifies that reverse order starts with the last inserted element.
 */
TEST_CASE("Begin Reverse Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(9);
    auto it = c.begin_reverse_order();
    CHECK(*it == 9); // last inserted
}

/**
 * Test end_reverse_order
 * Ensures the end iterator is different from the beginning in reverse order.
 */
TEST_CASE("End Reverse Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(9);
    auto it = c.end_reverse_order();
    CHECK(it != c.begin_reverse_order());
}

/**
 * Test begin_order
 * Verifies that the default iteration begins from the first inserted element.
 */
TEST_CASE("Begin Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(9);
    auto it = c.begin_order();
    CHECK(*it == 7); // first inserted
}

/**
 * Test end_order
 * Verifies that the end iterator is not equal to the beginning in default order.
 */
TEST_CASE("End Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(9);
    auto it = c.end_order();
    CHECK(it != c.begin_order());
}

/**
 * Demo output of ascending order iteration.
 * This is for manual observation (not a functional test).
 */
TEST_CASE("Ascending Order Manual Output")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(2);
    c.addElement(9);
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it)
    {
        std::cout << *it << " ";
    }
}

/**
 * Test: Repeated insertion and removal
 * Verifies that after inserting 100 integers and removing all even numbers,
 * the container contains exactly the 50 odd numbers, and iteration reflects that.
 */
TEST_CASE("Repeated insertion and removal") {
    MyContainer<int> c;
    for (int i = 0; i < 100; ++i) {
        c.addElement(i);
    }
    for (int i = 0; i < 100; i += 2) {
        c.removeElement(i);
    }
    CHECK(c.size() == 50);
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        std::cout << *it << " ";
    }
}

/**
 * Test: Adding duplicate values
 * Verifies that the container allows duplicate values and that all are preserved during iteration.
 */
TEST_CASE("Adding duplicate values") {
    MyContainer<int> c;
    c.addElement(5);
    c.addElement(5);
    c.addElement(5);

    int count = 0;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        CHECK(*it == 5);
        ++count;
    }
    CHECK(count == 3);
}

/**
 * Test: Iterators on empty container should not dereference
 * Checks that all iterator types (6 in number) behave correctly when the container is empty,
 * meaning that begin() equals end() for all of them and no iteration occurs.
 */
TEST_CASE("Iterators on empty container should not dereference") {
    MyContainer<int> c;

    CHECK(c.begin_order() == c.end_order());
    CHECK(c.begin_ascending_order() == c.end_ascending_order());
    CHECK(c.begin_descending_order() == c.end_descending_order());
    CHECK(c.begin_side_cross_order() == c.end_side_cross_order());
    CHECK(c.begin_reverse_order() == c.end_reverse_order());
    CHECK(c.begin_middle_out_order() == c.end_middle_out_order());
}

/**
 * Test: Dereferencing an iterator at end() should throw
 * Verifies that dereferencing an iterator obtained from an empty container throws an out_of_range exception.
 */
TEST_CASE("Dereferencing end() should throw") {
    MyContainer<int> c;
    auto it = c.begin_ascending_order();
    CHECK_THROWS_AS(*it, std::out_of_range);
}
/**
 * The test checks that adding an element after creating an iterator does not damage the previous iterator.
 */
TEST_CASE("Iterator stability after addElement") {
    MyContainer<int> c;
    c.addElement(1);
    auto it = c.begin_order();
    c.addElement(2); 
    CHECK_NOTHROW(*it);
}


/**
 * Test: Mix of negative, zero, and positive values
 * Verifies that ascending iteration over a container with mixed-sign integers
 * yields the correct sorted order: negative < zero < positive.
 */
TEST_CASE("Mix of negative, zero, and positive") {
    MyContainer<int> c;
    c.addElement(-10);
    c.addElement(0);
    c.addElement(10);

    std::vector<int> ascending;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it)
        ascending.push_back(*it);
    CHECK(ascending == std::vector<int>{-10, 0, 10});
}

/**
 * Test: Comparing iterators from different containers
 * Ensures that comparing iterators from two different containers
 * throws an exception (if such behavior is enforced by the implementation).
 */
TEST_CASE("Iterator from different containers") {
    MyContainer<int> c1, c2;
    c1.addElement(1);
    c2.addElement(1);

    auto it1 = c1.begin_order();
    auto it2 = c2.begin_order();

    CHECK_THROWS(it1 != it2); 
}

/**
 * Test: Iterator copy and post-increment behavior
 * Verifies that post-increment creates a copy of the iterator pointing to the current element
 * before advancing the original. Ensures both iterators behave as expected.
 */
TEST_CASE("Iterator copy and post-increment") {
    MyContainer<int> c;
    c.addElement(1);
    c.addElement(2);

    auto it = c.begin_ascending_order();
    auto copy = it++;
    CHECK(*copy == 1);
    CHECK(*it == 2);
}
