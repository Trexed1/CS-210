#include "Assignment05.h"

ArrayQueue::ArrayQueue() {
    front = 0;
    count = 0;
}

bool ArrayQueue::enqueue(int value) {
    if (count == CAPACITY) return false;
    int back = (front + count) % CAPACITY;
    data[back] = value;
    count++;
    return true;
}

bool ArrayQueue::dequeue(int& value) {
    if (count == 0) return false;
    value = data[front];
    front = (front + 1) % CAPACITY;
    count--;
    return true;
}

LinkedQueue::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
}

bool LinkedQueue::enqueue(int value) {
    Node* node = new Node;
    node->value = value;
    node->next = nullptr;

    if (tail == nullptr) head = node;
    else tail->next = node;
    tail = node;
    return true;
}

bool LinkedQueue::dequeue(int& value) {
    if (head == nullptr) return false;
    Node* old = head;
    value = old->value;
    head = head->next;
    if (head == nullptr) tail = nullptr;
    delete old;
    return true;
}

LinkedQueue::~LinkedQueue() {
    while (head != nullptr) {
        Node* old = head;
        head = head->next;
        delete old;
    }
}
