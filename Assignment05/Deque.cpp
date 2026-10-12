#include "Assignment05.h"

ArrayDeque::ArrayDeque() {
    front = 0;
    count = 0;
}

bool ArrayDeque::pushFront(int value) {
    if (count == CAPACITY) return false;
    front = (front + CAPACITY - 1) % CAPACITY;
    data[front] = value;
    count++;
    return true;
}

bool ArrayDeque::pushBack(int value) {
    if (count == CAPACITY) return false;
    int back = (front + count) % CAPACITY;
    data[back] = value;
    count++;
    return true;
}

bool ArrayDeque::popFront(int& value) {
    if (count == 0) return false;
    value = data[front];
    front = (front + 1) % CAPACITY;
    count--;
    return true;
}

bool ArrayDeque::popBack(int& value) {
    if (count == 0) return false;
    int back = (front + count - 1) % CAPACITY;
    value = data[back];
    count--;
    return true;
}

LinkedDeque::LinkedDeque() {
    head = nullptr;
    tail = nullptr;
}

bool LinkedDeque::pushFront(int value) {
    Node* node = new Node;
    node->value = value;
    node->previous = nullptr;
    node->next = head;
    if (head == nullptr) tail = node;
    else head->previous = node;
    head = node;
    return true;
}

bool LinkedDeque::pushBack(int value) {
    Node* node = new Node;
    node->value = value;
    node->previous = tail;
    node->next = nullptr;
    if (tail == nullptr) head = node;
    else tail->next = node;
    tail = node;
    return true;
}

bool LinkedDeque::popFront(int& value) {
    if (head == nullptr) return false;
    Node* old = head;
    value = old->value;
    head = head->next;
    if (head == nullptr) tail = nullptr;
    else head->previous = nullptr;
    delete old;
    return true;
}

bool LinkedDeque::popBack(int& value) {
    if (tail == nullptr) return false;
    Node* old = tail;
    value = old->value;
    tail = tail->previous;
    if (tail == nullptr) head = nullptr;
    else tail->next = nullptr;
    delete old;
    return true;
}

LinkedDeque::~LinkedDeque() {
    while (head != nullptr) {
        Node* old = head;
        head = head->next;
        delete old;
    }
}
