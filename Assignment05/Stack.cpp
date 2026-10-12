#include "Assignment05.h"

ArrayStack::ArrayStack() {
    count = 0;
}

bool ArrayStack::push(int value) {
    if (count == CAPACITY) return false;
    data[count] = value;
    count++;
    return true;
}

bool ArrayStack::pop(int& value) {
    if (count == 0) return false;
    count--;
    value = data[count];
    return true;
}

LinkedStack::LinkedStack() {
    head = nullptr;
}

bool LinkedStack::push(int value) {
    Node* node = new Node;
    node->value = value;
    node->next = head;
    head = node;
    return true;
}

bool LinkedStack::pop(int& value) {
    if (head == nullptr) return false;
    Node* old = head;
    value = old->value;
    head = head->next;
    delete old;
    return true;
}

LinkedStack::~LinkedStack() {
    while (head != nullptr) {
        Node* old = head;
        head = head->next;
        delete old;
    }
}
