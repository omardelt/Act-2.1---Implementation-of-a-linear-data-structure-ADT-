/*
 * Tests for the doubly linked list with sentinels (C++17).
 * From this directory:
 *   g++ -std=c++17 -Wall -Wextra -pedantic test_doubly_linked_list.cpp -o test_list
 *   ./test_list
 * Add -DUSE_SOLUTION to compile the tests against the solution header.
 * The template compiles, but tests will fail until the TODO methods are completed.
 * Student IDs:
 * Date: 
 */


#include <iostream>
#include <sstream>
#include <string>

#ifdef USE_SOLUTION
#include "doubly_linked_list_solution.h"
#else
#include "doubly_linked_list.h"
#endif

// Tests use only the public interface.
namespace {
int testsRun = 0;
int testsPassed = 0;

/**
 * Reports a test result and updates the running totals. Returns: none.
 * @param description Short explanation of the expected behavior.
 * @param passed True if the test passed, false otherwise.
 * Complexity: O(d), prints the description of length d.
 */
void check(const std::string &description, bool passed) {
    ++testsRun;
    if (passed) {
        ++testsPassed;
    }
    std::cout << (passed ? "PASS: " : "FAIL: ") << description << '\n';
}

/**
 * Captures print() output without changing the list.
 * Restores std::cout before returning or propagating an exception.
 * @param list List whose printed representation is captured.
 * @return Printed elements, including brackets and the trailing newline.
 * Complexity: O(n + c), visits n elements and copies c output characters,
 * assuming each element takes constant time to format.
 */
template <typename T>
std::string printedForm(const DoublyLinkedList<T> &list) {
    std::ostringstream output;
    std::streambuf *previous = std::cout.rdbuf(output.rdbuf());
    try {
        list.print();
    } catch (...) {
        std::cout.rdbuf(previous);
        throw;
    }
    std::cout.rdbuf(previous);
    return output.str();
}
} // namespace

/**
 * Runs insertion, search, removal, and printing tests. Parameters: none.
 * Covers empty lists, single elements, duplicates, and string values.
 * Prints individual results and the total number of passing tests.
 * @return 0 if all tests pass, 1 otherwise.
 * Complexity: O(1), uses a fixed number of tests and elements.
 */
int main() {
    DoublyLinkedList<int> list;
    check("empty print", printedForm(list) == "[  ]\n");
    check("search excludes sentinels", !list.search(0));
    check("remove excludes sentinels", !list.remove(0));
    check("removeFront on empty", !list.removeFront());
    check("removeBack on empty", !list.removeBack());

    list.insertFront(20);
    list.insertFront(10);
    list.insertBack(30);
    check("mixed insertions preserve order", printedForm(list) == "[ 10, 20, 30 ]\n");
    check("search first", list.search(10));
    check("search middle", list.search(20));
    check("search last", list.search(30));
    check("search absent", !list.search(99));
    check("remove absent", !list.remove(99));
    check("search and failed remove preserve list", printedForm(list) == "[ 10, 20, 30 ]\n");
    check("remove middle", list.remove(20));
    check("middle removed, neighbors preserved", printedForm(list) == "[ 10, 30 ]\n");
    check("remove front", list.removeFront());
    check("front removed", printedForm(list) == "[ 30 ]\n");
    check("remove back singleton", list.removeBack());
    check("empty again", printedForm(list) == "[  ]\n");
    check("removeFront after emptying", !list.removeFront());
    check("removeBack after emptying", !list.removeBack());

    list.insertBack(0);
    check("default value is a valid element", list.search(0));
    check("remove singleton by value", list.remove(0));
    check("default value absent after removal", !list.search(0));
    check("singleton removal restores empty list", printedForm(list) == "[  ]\n");
    list.insertFront(7);
    check("remove front singleton", list.removeFront());
    check("front singleton removal restores empty list", printedForm(list) == "[  ]\n");

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(1);
    list.insertBack(3);
    check("remove first matching duplicate", list.remove(1));
    check("later duplicate remains in order", printedForm(list) == "[ 2, 1, 3 ]\n");
    check("remove last by value", list.remove(3));
    check("back links after value removal", list.removeBack());
    check("correct back removed", printedForm(list) == "[ 2 ]\n");
    check("remove remaining first by value", list.remove(2));
    check("list reusable after removals", printedForm(list) == "[  ]\n");

    DoublyLinkedList<std::string> words;
    words.insertBack("world");
    words.insertFront("hello");
    check("string instantiation and order", printedForm(words) == "[ hello, world ]\n");
    check("string search", words.search("world"));
    check("string remove", words.remove("hello"));
    check("string remainder", printedForm(words) == "[ world ]\n");
    // words remains nonempty to exercise destruction with live elements.

    std::cout << "RESULT passed=" << testsPassed << " of=" << testsRun << '\n';
    return testsPassed == testsRun ? 0 : 1;
}
