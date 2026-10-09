#include "Assignment05.h"
#include <iostream>

using namespace std;

const int STACK_CAPACITY = 5;

class ArrayStack {
private:
    int data[STACK_CAPACITY];
    int count;

public:
    ArrayStack() { count = 0; }

    bool push(int value) {
        if (count == STACK_CAPACITY) return false;
        data[count] = value;
        count++;
        return true;
    }

    bool pop(int& value) {
        if (count == 0) return false;
        count--;
        value = data[count];
        return true;
    }

    bool isEmpty() { return count == 0; }
    int size() { return count; }
};

class LinkedStack {
private:
    struct Node {
        int value;
        Node* next;
    };
    Node* head;
    int count;

public:
    LinkedStack() {
        head = nullptr;
        count = 0;
    }

    bool push(int value) {
        Node* node = new Node;
        node->value = value;
        node->next = head;
        head = node;
        count++;
        return true;
    }

    bool pop(int& value) {
        if (head == nullptr) return false;
        Node* old = head;
        value = old->value;
        head = head->next;
        delete old;
        count--;
        return true;
    }

    bool isEmpty() { return head == nullptr; }
    int size() { return count; }

    ~LinkedStack() {
        while (head != nullptr) {
            Node* old = head;
            head = head->next;
            delete old;
        }
    }
};

void testStacks(int& totalSteps, int& failures) {
    int steps = 0;
    int value;
    bool success;

    cout << "\nARRAY STACK" << endl;
    ArrayStack arrayStack;
    value = -1; // Failed removal must not change this value.
    success = arrayStack.pop(value);
    checkRemove("pop", success, value, false, -1, steps, failures);
    success = arrayStack.push(10);
    checkInsert("push 10", success, true, steps, failures);
    success = arrayStack.push(20);
    checkInsert("push 20", success, true, steps, failures);
    success = arrayStack.push(30);
    checkInsert("push 30", success, true, steps, failures);
    success = arrayStack.pop(value);
    checkRemove("pop", success, value, true, 30, steps, failures);
    success = arrayStack.push(40);
    checkInsert("push 40", success, true, steps, failures);
    success = arrayStack.push(50);
    checkInsert("push 50", success, true, steps, failures);
    success = arrayStack.push(60);
    checkInsert("push 60", success, true, steps, failures);
    success = arrayStack.push(99);
    checkInsert("push 99 while full", success, false, steps, failures);
    success = arrayStack.pop(value);
    checkRemove("pop", success, value, true, 60, steps, failures);
    success = arrayStack.pop(value);
    checkRemove("pop", success, value, true, 50, steps, failures);
    success = arrayStack.push(70);
    checkInsert("push 70", success, true, steps, failures);
    success = arrayStack.pop(value);
    checkRemove("pop", success, value, true, 70, steps, failures);
    success = arrayStack.pop(value);
    checkRemove("pop", success, value, true, 40, steps, failures);
    success = arrayStack.pop(value);
    checkRemove("pop", success, value, true, 20, steps, failures);
    success = arrayStack.pop(value);
    checkRemove("pop", success, value, true, 10, steps, failures);
    value = -1; // Failed removal must not change this value.
    success = arrayStack.pop(value);
    checkRemove("pop", success, value, false, -1, steps, failures);
    if (!arrayStack.isEmpty() || arrayStack.size() != 0) failures++;
    cout << "Operations: " << steps << "; final size: " << arrayStack.size() << endl;
    totalSteps += steps;

    cout << "\nLINKED STACK" << endl;
    LinkedStack linkedStack;
    steps = 0;
    value = -1; // Failed removal must not change this value.
    success = linkedStack.pop(value);
    checkRemove("pop", success, value, false, -1, steps, failures);
    success = linkedStack.push(10);
    checkInsert("push 10", success, true, steps, failures);
    success = linkedStack.push(20);
    checkInsert("push 20", success, true, steps, failures);
    success = linkedStack.push(30);
    checkInsert("push 30", success, true, steps, failures);
    success = linkedStack.pop(value);
    checkRemove("pop", success, value, true, 30, steps, failures);
    success = linkedStack.push(40);
    checkInsert("push 40", success, true, steps, failures);
    success = linkedStack.push(50);
    checkInsert("push 50", success, true, steps, failures);
    success = linkedStack.push(60);
    checkInsert("push 60", success, true, steps, failures);
    success = linkedStack.pop(value);
    checkRemove("pop", success, value, true, 60, steps, failures);
    success = linkedStack.pop(value);
    checkRemove("pop", success, value, true, 50, steps, failures);
    success = linkedStack.push(70);
    checkInsert("push 70", success, true, steps, failures);
    success = linkedStack.pop(value);
    checkRemove("pop", success, value, true, 70, steps, failures);
    success = linkedStack.pop(value);
    checkRemove("pop", success, value, true, 40, steps, failures);
    success = linkedStack.pop(value);
    checkRemove("pop", success, value, true, 20, steps, failures);
    success = linkedStack.pop(value);
    checkRemove("pop", success, value, true, 10, steps, failures);
    value = -1; // Failed removal must not change this value.
    success = linkedStack.pop(value);
    checkRemove("pop", success, value, false, -1, steps, failures);
    if (!linkedStack.isEmpty() || linkedStack.size() != 0) failures++;
    cout << "Operations: " << steps << "; final size: " << linkedStack.size() << endl;
    totalSteps += steps;
}
