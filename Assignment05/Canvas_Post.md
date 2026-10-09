# Assignment 05: Stacks, Queues, and Deques

Tyler Rex | CS 210 | C++17

**PDF attachment:** `Rex_Tyler_Assignment05.pdf` (attach the one PDF from `output/pdf/` to this Canvas post).

**GitHub repository:** https://github.com/Trexed1/CS-210

**Submitted version:** tag [`assignment05-submission-v2`](https://github.com/Trexed1/CS-210/tree/assignment05-submission-v2/Assignment05)

## Design

I put the two stack implementations in `Stack.cpp`, the two queues in `Queue.cpp`, and the two deques in `Deque.cpp`. `main.cpp` only checks and prints results and calls the three demonstration functions. `Assignment05.h` contains the shared function declarations. I used regular classes, functions, arrays, and my own linked nodes; there are no templates or `auto` variables.

The array stack has a five-element array and a count. The linked stack adds and removes at its head. The array queue and deque use circular arrays so values do not shift. The linked queue keeps head and tail pointers, and the linked deque uses previous and next pointers to change either end.

Insertion returns `false` when a fixed array is full. Removal returns `false` when empty and leaves the output value unchanged. The linked classes delete remaining nodes in their destructors.

## Tests and results

I compiled with `clang++ -std=c++17 -Wall -Wextra main.cpp Stack.cpp Queue.cpp Deque.cpp -o assignment05` and ran `./assignment05`. The program performs 101 checked operations across the six structures, with at least 16 per structure. The checks cover empty removals, full-array insertions, LIFO and FIFO order, circular wraparound, and both deque ends. The actual run ended with `TOTAL: 101 operations; 0 failures`. A sanitizer build also finished without errors. The PDF contains the full output.

## Complexity

Every insertion and removal in these designs is O(1), as are `isEmpty()` and `size()`. Fixed arrays use O(C) space, where C = 5; linked versions use O(n) space for n items. Deleting n leftover linked nodes is O(n). A growing array could take O(n) when it copies values, an array queue that shifts items could take O(n) per removal, and a singly linked deque could take O(n) to remove from the back. Circular indexing and previous pointers avoid those costs here.

## Complete source code

### Assignment05.h

```cpp
#ifndef ASSIGNMENT05_H
#define ASSIGNMENT05_H

#include <string>

using namespace std;

// These functions print one operation and compare it with the expected result.
void checkInsert(string action, bool actual, bool expected,
                 int& steps, int& failures);
void checkRemove(string action, bool actual, int value,
                 bool expected, int expectedValue, int& steps, int& failures);

// Each function demonstrates the array and linked versions of one ADT.
void testStacks(int& totalSteps, int& failures);
void testQueues(int& totalSteps, int& failures);
void testDeques(int& totalSteps, int& failures);

#endif
```

### Stack.cpp

```cpp
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
```

### Queue.cpp

```cpp
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
```

### Deque.cpp

```cpp
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
```

### main.cpp

```cpp
#include "Assignment05.h"
#include <iostream>

using namespace std;

void checkInsert(string action, bool actual, bool expected,
                 int& steps, int& failures) {
    steps++;
    bool passed = (actual == expected);
    if (!passed) failures++;

    cout << steps << ". " << action << " -> ";
    if (actual) cout << "success";
    else cout << "rejected";
    if (passed) cout << " [PASS]" << endl;
    else cout << " [FAIL]" << endl;
}

void checkRemove(string action, bool actual, int value,
                 bool expected, int expectedValue, int& steps, int& failures) {
    steps++;
    bool passed = (actual == expected && value == expectedValue);
    if (!passed) failures++;

    cout << steps << ". " << action << " -> ";
    if (actual) cout << value;
    else cout << "empty";
    if (passed) cout << " [PASS]" << endl;
    else cout << " [FAIL]" << endl;
}

int main() {
    int totalSteps = 0;
    int failures = 0;

    testStacks(totalSteps, failures);
    testQueues(totalSteps, failures);
    testDeques(totalSteps, failures);

    cout << "\nTOTAL: " << totalSteps << " operations; "
         << failures << " failures" << endl;

    if (failures == 0) return 0;
    return 1;
}
```
