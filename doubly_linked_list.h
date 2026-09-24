/*
 * Doubly linked list exercise with front and back sentinels. Requires C++17.
 * Student IDs: A01648827, A01648573, A01647837, A00844255
 * Modified: 2026-09-24
 *
 * Replace the student ID placeholders and complete the six TODO methods.
 * Keep declarations unchanged; do not use break or continue in loops.
 * Complete each missing complexity with its order and a brief reason.
 * Placeholder bodies compile but do not implement the required operations.
 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

// Sentinels hold no list elements: an empty list links head directly to tail.
// T must support default construction, copying, ==, and stream output as used.
template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value = T{}, Node* previous = nullptr, Node* following = nullptr);
    };

    Node* head;       // Front sentinel.
    Node* tail;       // Back sentinel.
    int numElements;  // Excludes both sentinels.

    void insertBefore(Node* position, const T& value);

    void removeNode(Node* node);

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList& other) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList& other) = delete;

    void insertFront(const T& value);
    void insertBack(const T& value);
    bool search(const T& value) const;
    bool removeFront();
    bool removeBack();
    bool remove(const T& value);
    void print() const;
};

/**
 * Builds a node. Returns: none.
 * @param value Stored value; default constructed for sentinels.
 * @param previous Previous node, or nullptr.
 * @param following Next node, or nullptr.
 */
template <typename T>
DoublyLinkedList<T>::Node::Node(const T& value, Node* previous, Node* following)
    : data(value), prev(previous), next(following) {}

/**
 * Inserts before position and updates the count. Returns: none.
 * @param position Real node or tail sentinel; never head or nullptr.
 * @param value Element to insert.
 * Complexity: O(1), updates neighboring links.
 */
template <typename T>
void DoublyLinkedList<T>::insertBefore(Node* position, const T& value) {
    Node* newNode = new Node(value, position->prev, position);
    position->prev->next = newNode;
    position->prev = newNode;
    numElements++;
}

/**
 * Unlinks and deletes a node; updates the count. Returns: none.
 * @param node Real node in this list; never a sentinel or nullptr.
 * Complexity: O(1), updates neighboring links.
 */
template <typename T>
void DoublyLinkedList<T>::removeNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    numElements--;
}

/**
 * Builds an empty list with two sentinels. Parameters: none. Returns: none.
 * Complexity: O(1), creates and links two nodes.
 */
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(new Node()), tail(nullptr), numElements(0) {
    try {
        tail = new Node();
    } catch (...) {
        delete head;
        throw;
    }
    head->next = tail;
    tail->prev = head;
}

/**
 * Releases all nodes, including sentinels. Parameters: none. Returns: none.
 * Complexity: O(n), deletes each real node and both sentinels.
 */
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* current = head->next;
    while (current != tail) {
        Node* following = current->next;
        delete current;
        current = following;
    }
    delete head;
    delete tail;
}

/**
 * Inserts at the front. Returns: none.
 * @param value Element to insert.
 * TODO: Use insertBefore with the node after head.
 * Complexity: O(1) - inserts the new node before the first node
 */
template <typename T>
void DoublyLinkedList<T>::insertFront(const T& value) {
    insertBefore(head->next, value);
}

/**
 * Inserts at the back. Returns: none.
 * @param value Element to insert.
 * TODO: Use insertBefore with tail.
 * Complexity: O(1) - inserts the new node before the tail
 */
template <typename T>
void DoublyLinkedList<T>::insertBack(const T& value) {
    insertBefore(tail, value);
}

/**
 * Checks whether a value is present.
 * @param value Element to search for.
 * @return True if found, false otherwise.
 * TODO: Traverse from head->next to tail, excluding both sentinels.
 * Complexity: O(n) - inspects every real node until the value is found.
 */
template <typename T>
bool DoublyLinkedList<T>::search(const T& value) const {
    Node* curr = head->next;

    while (curr != tail) {
        if (curr->data == value)
            return true;

        curr = curr->next;
    }
    return false;
}

/**
 * Removes the first element. Parameters: none.
 * @return True if removed, false if empty.
 * TODO: Check the count, then use removeNode on head->next.
 * Complexity: O(1) - removes the first real node.
 */
template <typename T>
bool DoublyLinkedList<T>::removeFront() {
    if (numElements > 0) {
        removeNode(head->next);
        return true;
    }
    return false;
}

/**
 * Removes the last element. Parameters: none.
 * @return True if removed, false if empty.
 * TODO: Check the count, then use removeNode on tail->prev.
 * Complexity: O(1) - removes the last real node directly.
 */
template <typename T>
bool DoublyLinkedList<T>::removeBack() {
    if (numElements > 0) {
        removeNode(tail->prev);
        return true;
    }
    return false;
}

/**
 * Removes the first matching element.
 * @param value Element to remove.
 * @return True if removed, false if absent.
 * TODO: Search real nodes and use removeNode on the first match.
 * Complexity: O(n) - inspects every real node until the value is found, and then it is removed.
 */
template <typename T>
bool DoublyLinkedList<T>::remove(const T& value) {
    Node* current = head->next;
    while (current != tail) {
        if (current->data == value) {
            removeNode(current);
            return true;
        }
        current = current->next;
    }
    return false;
}

/**
 * Prints real elements from first to last. Parameters: none. Returns: none.
 * Complexity: O(n) - visits each real node once.
 */
template <typename T>
void DoublyLinkedList<T>::print() const {
    Node* current = head->next;
    std::cout << "[ ";
    while (current != tail) {
        std::cout << current->data;
        if (current->next != tail) {
            std::cout << ", ";
        }
        current = current->next;
    }
    std::cout << " ]" << std::endl;
}

#endif
