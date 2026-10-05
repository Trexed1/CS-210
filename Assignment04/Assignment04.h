#ifndef ASSIGNMENT04_H
#define ASSIGNMENT04_H

#include <iostream>
#include <string>

using namespace std;

struct Node {
    string name;
    int cost;
    string owner;
    Node* next;
};


class LinkedList {
private:
    Node* head;
    Node* tail;
    bool circular;

public:
    LinkedList();

    void add(string name, int cost);
    Node* search(string name);
    bool remove(string name);
    void print();

    void makeCircular();

    Node* getHead();
    Node* getTail();

    ~LinkedList();
};


class MonopolyBoard {
private:
    LinkedList board;

public:
    MonopolyBoard();

    void printBoard();

    Node* getStart();

    Node* movePlayer(Node* currentPosition, int spaces);

    bool purchaseProperty(Node* property, string playerName);
};

#endif