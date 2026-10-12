#ifndef ASSIGNMENT05_H
#define ASSIGNMENT05_H

const int CAPACITY = 5;

class ArrayStack {
private:
    int data[CAPACITY];
    int count;

public:
    ArrayStack();
    bool push(int value);
    bool pop(int& value);
};

class LinkedStack {
private:
    struct Node {
        int value;
        Node* next;
    };
    Node* head;

public:
    LinkedStack();
    bool push(int value);
    bool pop(int& value);
    ~LinkedStack();
};

class ArrayQueue {
private:
    int data[CAPACITY];
    int front;
    int count;

public:
    ArrayQueue();
    bool enqueue(int value);
    bool dequeue(int& value);
};

class LinkedQueue {
private:
    struct Node {
        int value;
        Node* next;
    };
    Node* head;
    Node* tail;

public:
    LinkedQueue();
    bool enqueue(int value);
    bool dequeue(int& value);
    ~LinkedQueue();
};

class ArrayDeque {
private:
    int data[CAPACITY];
    int front;
    int count;

public:
    ArrayDeque();
    bool pushFront(int value);
    bool pushBack(int value);
    bool popFront(int& value);
    bool popBack(int& value);
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

public:
    LinkedDeque();
    bool pushFront(int value);
    bool pushBack(int value);
    bool popFront(int& value);
    bool popBack(int& value);
    ~LinkedDeque();
};

#endif
