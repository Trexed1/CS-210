#include "Assignment05.h"
#include <iostream>

using namespace std;

const int QUEUE_CAPACITY = 5;

class ArrayQueue {
private:
    int data[QUEUE_CAPACITY];
    int front;
    int count;

public:
    ArrayQueue() {
        front = 0;
        count = 0;
    }

    bool enqueue(int value) {
        if (count == QUEUE_CAPACITY) return false;
        int back = (front + count) % QUEUE_CAPACITY;
        data[back] = value;
        count++;
        return true;
    }

    bool dequeue(int& value) {
        if (count == 0) return false;
        value = data[front];
        front = (front + 1) % QUEUE_CAPACITY;
        count--;
        return true;
    }

    bool isEmpty() { return count == 0; }
    int size() { return count; }
};

class LinkedQueue {
private:
    struct Node {
        int value;
        Node* next;
    };
    Node* head;
    Node* tail;
    int count;

public:
    LinkedQueue() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    bool enqueue(int value) {
        Node* node = new Node;
        node->value = value;
        node->next = nullptr;

        if (tail == nullptr) head = node;
        else tail->next = node;
        tail = node;
        count++;
        return true;
    }

    bool dequeue(int& value) {
        if (head == nullptr) return false;
        Node* old = head;
        value = old->value;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete old;
        count--;
        return true;
    }

    bool isEmpty() { return head == nullptr; }
    int size() { return count; }

    ~LinkedQueue() {
        while (head != nullptr) {
            Node* old = head;
            head = head->next;
            delete old;
        }
    }
};

void testQueues(int& totalSteps, int& failures) {
    int steps = 0;
    int value;
    bool success;

    cout << "\nARRAY QUEUE" << endl;
    ArrayQueue arrayQueue;
    value = -1; // Failed removal must not change this value.
    success = arrayQueue.dequeue(value);
    checkRemove("dequeue", success, value, false, -1, steps, failures);
    success = arrayQueue.enqueue(10);
    checkInsert("enqueue 10", success, true, steps, failures);
    success = arrayQueue.enqueue(20);
    checkInsert("enqueue 20", success, true, steps, failures);
    success = arrayQueue.enqueue(30);
    checkInsert("enqueue 30", success, true, steps, failures);
    success = arrayQueue.enqueue(40);
    checkInsert("enqueue 40", success, true, steps, failures);
    success = arrayQueue.enqueue(50);
    checkInsert("enqueue 50", success, true, steps, failures);
    success = arrayQueue.enqueue(99);
    checkInsert("enqueue 99 while full", success, false, steps, failures);
    success = arrayQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 10, steps, failures);
    success = arrayQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 20, steps, failures);
    success = arrayQueue.enqueue(60);
    checkInsert("enqueue 60", success, true, steps, failures);
    success = arrayQueue.enqueue(70);
    checkInsert("enqueue 70", success, true, steps, failures);
    success = arrayQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 30, steps, failures);
    success = arrayQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 40, steps, failures);
    success = arrayQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 50, steps, failures);
    success = arrayQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 60, steps, failures);
    success = arrayQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 70, steps, failures);
    value = -1; // Failed removal must not change this value.
    success = arrayQueue.dequeue(value);
    checkRemove("dequeue", success, value, false, -1, steps, failures);
    if (!arrayQueue.isEmpty() || arrayQueue.size() != 0) failures++;
    cout << "Operations: " << steps << "; final size: " << arrayQueue.size() << endl;
    totalSteps += steps;

    cout << "\nLINKED QUEUE" << endl;
    LinkedQueue linkedQueue;
    steps = 0;
    value = -1; // Failed removal must not change this value.
    success = linkedQueue.dequeue(value);
    checkRemove("dequeue", success, value, false, -1, steps, failures);
    success = linkedQueue.enqueue(10);
    checkInsert("enqueue 10", success, true, steps, failures);
    success = linkedQueue.enqueue(20);
    checkInsert("enqueue 20", success, true, steps, failures);
    success = linkedQueue.enqueue(30);
    checkInsert("enqueue 30", success, true, steps, failures);
    success = linkedQueue.enqueue(40);
    checkInsert("enqueue 40", success, true, steps, failures);
    success = linkedQueue.enqueue(50);
    checkInsert("enqueue 50", success, true, steps, failures);
    success = linkedQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 10, steps, failures);
    success = linkedQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 20, steps, failures);
    success = linkedQueue.enqueue(60);
    checkInsert("enqueue 60", success, true, steps, failures);
    success = linkedQueue.enqueue(70);
    checkInsert("enqueue 70", success, true, steps, failures);
    success = linkedQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 30, steps, failures);
    success = linkedQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 40, steps, failures);
    success = linkedQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 50, steps, failures);
    success = linkedQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 60, steps, failures);
    success = linkedQueue.dequeue(value);
    checkRemove("dequeue", success, value, true, 70, steps, failures);
    value = -1; // Failed removal must not change this value.
    success = linkedQueue.dequeue(value);
    checkRemove("dequeue", success, value, false, -1, steps, failures);
    if (!linkedQueue.isEmpty() || linkedQueue.size() != 0) failures++;
    cout << "Operations: " << steps << "; final size: " << linkedQueue.size() << endl;
    totalSteps += steps;
}
