#include "Assignment05.h"
#include <iostream>

using namespace std;

const int DEQUE_CAPACITY = 5;

class ArrayDeque {
private:
    int data[DEQUE_CAPACITY];
    int front;
    int count;

public:
    ArrayDeque() {
        front = 0;
        count = 0;
    }

    bool pushFront(int value) {
        if (count == DEQUE_CAPACITY) return false;
        front = (front + DEQUE_CAPACITY - 1) % DEQUE_CAPACITY;
        data[front] = value;
        count++;
        return true;
    }

    bool pushBack(int value) {
        if (count == DEQUE_CAPACITY) return false;
        int back = (front + count) % DEQUE_CAPACITY;
        data[back] = value;
        count++;
        return true;
    }

    bool popFront(int& value) {
        if (count == 0) return false;
        value = data[front];
        front = (front + 1) % DEQUE_CAPACITY;
        count--;
        return true;
    }

    bool popBack(int& value) {
        if (count == 0) return false;
        int back = (front + count - 1) % DEQUE_CAPACITY;
        value = data[back];
        count--;
        return true;
    }

    bool isEmpty() { return count == 0; }
    int size() { return count; }
};

class LinkedDeque {
private:
    struct Node {
        int value;
        Node* previous;
        Node* next;
    };
    Node* head;
    Node* tail;
    int count;

public:
    LinkedDeque() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    bool pushFront(int value) {
        Node* node = new Node;
        node->value = value;
        node->previous = nullptr;
        node->next = head;
        if (head == nullptr) tail = node;
        else head->previous = node;
        head = node;
        count++;
        return true;
    }

    bool pushBack(int value) {
        Node* node = new Node;
        node->value = value;
        node->previous = tail;
        node->next = nullptr;
        if (tail == nullptr) head = node;
        else tail->next = node;
        tail = node;
        count++;
        return true;
    }

    bool popFront(int& value) {
        if (head == nullptr) return false;
        Node* old = head;
        value = old->value;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        else head->previous = nullptr;
        delete old;
        count--;
        return true;
    }

    bool popBack(int& value) {
        if (tail == nullptr) return false;
        Node* old = tail;
        value = old->value;
        tail = tail->previous;
        if (tail == nullptr) head = nullptr;
        else tail->next = nullptr;
        delete old;
        count--;
        return true;
    }

    bool isEmpty() { return head == nullptr; }
    int size() { return count; }

    ~LinkedDeque() {
        while (head != nullptr) {
            Node* old = head;
            head = head->next;
            delete old;
        }
    }
};

void testDeques(int& totalSteps, int& failures) {
    int steps = 0;
    int value;
    bool success;

    cout << "\nARRAY DEQUE" << endl;
    ArrayDeque arrayDeque;
    value = -1; // Failed removal must not change this value.
    success = arrayDeque.popFront(value);
    checkRemove("popFront", success, value, false, -1, steps, failures);
    success = arrayDeque.pushBack(10);
    checkInsert("pushBack 10", success, true, steps, failures);
    success = arrayDeque.pushFront(20);
    checkInsert("pushFront 20", success, true, steps, failures);
    success = arrayDeque.pushBack(30);
    checkInsert("pushBack 30", success, true, steps, failures);
    success = arrayDeque.popBack(value);
    checkRemove("popBack", success, value, true, 30, steps, failures);
    success = arrayDeque.pushFront(40);
    checkInsert("pushFront 40", success, true, steps, failures);
    success = arrayDeque.pushBack(50);
    checkInsert("pushBack 50", success, true, steps, failures);
    success = arrayDeque.popFront(value);
    checkRemove("popFront", success, value, true, 40, steps, failures);
    success = arrayDeque.pushBack(60);
    checkInsert("pushBack 60", success, true, steps, failures);
    success = arrayDeque.popBack(value);
    checkRemove("popBack", success, value, true, 60, steps, failures);
    success = arrayDeque.pushFront(70);
    checkInsert("pushFront 70", success, true, steps, failures);
    success = arrayDeque.pushBack(80);
    checkInsert("pushBack 80", success, true, steps, failures);
    success = arrayDeque.pushFront(99);
    checkInsert("pushFront 99 while full", success, false, steps, failures);
    success = arrayDeque.popBack(value);
    checkRemove("popBack", success, value, true, 80, steps, failures);
    success = arrayDeque.popFront(value);
    checkRemove("popFront", success, value, true, 70, steps, failures);
    success = arrayDeque.popFront(value);
    checkRemove("popFront", success, value, true, 20, steps, failures);
    success = arrayDeque.popBack(value);
    checkRemove("popBack", success, value, true, 50, steps, failures);
    success = arrayDeque.popBack(value);
    checkRemove("popBack", success, value, true, 10, steps, failures);
    value = -1; // Failed removal must not change this value.
    success = arrayDeque.popBack(value);
    checkRemove("popBack", success, value, false, -1, steps, failures);
    if (!arrayDeque.isEmpty() || arrayDeque.size() != 0) failures++;
    cout << "Operations: " << steps << "; final size: " << arrayDeque.size() << endl;
    totalSteps += steps;

    cout << "\nLINKED DEQUE" << endl;
    LinkedDeque linkedDeque;
    steps = 0;
    value = -1; // Failed removal must not change this value.
    success = linkedDeque.popFront(value);
    checkRemove("popFront", success, value, false, -1, steps, failures);
    success = linkedDeque.pushBack(10);
    checkInsert("pushBack 10", success, true, steps, failures);
    success = linkedDeque.pushFront(20);
    checkInsert("pushFront 20", success, true, steps, failures);
    success = linkedDeque.pushBack(30);
    checkInsert("pushBack 30", success, true, steps, failures);
    success = linkedDeque.popBack(value);
    checkRemove("popBack", success, value, true, 30, steps, failures);
    success = linkedDeque.pushFront(40);
    checkInsert("pushFront 40", success, true, steps, failures);
    success = linkedDeque.pushBack(50);
    checkInsert("pushBack 50", success, true, steps, failures);
    success = linkedDeque.popFront(value);
    checkRemove("popFront", success, value, true, 40, steps, failures);
    success = linkedDeque.pushBack(60);
    checkInsert("pushBack 60", success, true, steps, failures);
    success = linkedDeque.popBack(value);
    checkRemove("popBack", success, value, true, 60, steps, failures);
    success = linkedDeque.pushFront(70);
    checkInsert("pushFront 70", success, true, steps, failures);
    success = linkedDeque.popFront(value);
    checkRemove("popFront", success, value, true, 70, steps, failures);
    success = linkedDeque.popFront(value);
    checkRemove("popFront", success, value, true, 20, steps, failures);
    success = linkedDeque.popBack(value);
    checkRemove("popBack", success, value, true, 50, steps, failures);
    success = linkedDeque.popBack(value);
    checkRemove("popBack", success, value, true, 10, steps, failures);
    value = -1; // Failed removal must not change this value.
    success = linkedDeque.popBack(value);
    checkRemove("popBack", success, value, false, -1, steps, failures);
    if (!linkedDeque.isEmpty() || linkedDeque.size() != 0) failures++;
    cout << "Operations: " << steps << "; final size: " << linkedDeque.size() << endl;
    totalSteps += steps;
}
