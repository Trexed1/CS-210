#include "Assignment05.h"
#include <iostream>

using namespace std;

int main() {
    ArrayStack arrayStack;
    LinkedStack linkedStack;
    ArrayQueue arrayQueue;
    LinkedQueue linkedQueue;
    ArrayDeque arrayDeque;
    LinkedDeque linkedDeque;
    int arrayValue = 0;
    int linkedValue = 0;

    // Stack: five pushes and five pops for each version.
    arrayStack.push(10);
    arrayStack.push(20);
    arrayStack.push(30);
    arrayStack.push(40);
    arrayStack.push(50);
    linkedStack.push(10);
    linkedStack.push(20);
    linkedStack.push(30);
    linkedStack.push(40);
    linkedStack.push(50);

    if (!arrayStack.push(60)) cout << "Array stack full" << endl;
    cout << "Stack pops (array, linked):" << endl;
    arrayStack.pop(arrayValue);
    linkedStack.pop(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    arrayStack.pop(arrayValue);
    linkedStack.pop(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    arrayStack.pop(arrayValue);
    linkedStack.pop(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    arrayStack.pop(arrayValue);
    linkedStack.pop(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    arrayStack.pop(arrayValue);
    linkedStack.pop(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    if (!arrayStack.pop(arrayValue)) cout << "Array stack empty" << endl;
    if (!linkedStack.pop(linkedValue)) cout << "Linked stack empty" << endl;

    // Queue: five enqueues and five dequeues for each version.
    arrayQueue.enqueue(10);
    arrayQueue.enqueue(20);
    arrayQueue.enqueue(30);
    arrayQueue.enqueue(40);
    arrayQueue.enqueue(50);
    linkedQueue.enqueue(10);
    linkedQueue.enqueue(20);
    linkedQueue.enqueue(30);
    linkedQueue.enqueue(40);
    linkedQueue.enqueue(50);

    if (!arrayQueue.enqueue(60)) cout << "Array queue full" << endl;
    cout << "Queue dequeues (array, linked):" << endl;
    arrayQueue.dequeue(arrayValue);
    linkedQueue.dequeue(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    arrayQueue.dequeue(arrayValue);
    linkedQueue.dequeue(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    arrayQueue.dequeue(arrayValue);
    linkedQueue.dequeue(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    arrayQueue.dequeue(arrayValue);
    linkedQueue.dequeue(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    arrayQueue.dequeue(arrayValue);
    linkedQueue.dequeue(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    if (!arrayQueue.dequeue(arrayValue)) cout << "Array queue empty" << endl;
    if (!linkedQueue.dequeue(linkedValue)) cout << "Linked queue empty" << endl;

    // Deque: five insertions and five removals for each version.
    arrayDeque.pushFront(10);
    arrayDeque.pushFront(20);
    arrayDeque.pushFront(30);
    arrayDeque.pushBack(40);
    arrayDeque.pushBack(50);
    linkedDeque.pushFront(10);
    linkedDeque.pushFront(20);
    linkedDeque.pushFront(30);
    linkedDeque.pushBack(40);
    linkedDeque.pushBack(50);

    if (!arrayDeque.pushBack(60)) cout << "Array deque full" << endl;
    cout << "Deque popFront (array, linked):" << endl;
    arrayDeque.popFront(arrayValue);
    linkedDeque.popFront(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    arrayDeque.popFront(arrayValue);
    linkedDeque.popFront(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    arrayDeque.popFront(arrayValue);
    linkedDeque.popFront(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    cout << "Deque popBack (array, linked):" << endl;
    arrayDeque.popBack(arrayValue);
    linkedDeque.popBack(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    arrayDeque.popBack(arrayValue);
    linkedDeque.popBack(linkedValue);
    cout << arrayValue << ", " << linkedValue << endl;
    if (!arrayDeque.popFront(arrayValue)) cout << "Array deque empty" << endl;
    if (!linkedDeque.popBack(linkedValue)) cout << "Linked deque empty" << endl;

    return 0;
}
