#include "Assignment04.h"

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    circular = false;
}

void LinkedList::add(string name, int cost) {
    Node* newNode = new Node;

    newNode->name = name;
    newNode->cost = cost;
    newNode->owner = "Unowned";
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

Node* LinkedList::search(string name) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* current = head;

    if (!circular) {
        while (current != nullptr) {
            if (current->name == name) {
                return current;
            }

            current = current->next;
        }
    }
    else {
        do {
            if (current->name == name) {
                return current;
            }

            current = current->next;

        } while (current != head);
    }

    return nullptr;
}

bool LinkedList::remove(string name) {
    if (head == nullptr) {
        return false;
    }

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->name == name) {

            if (current == head) {
                head = head->next;

                if (current == tail) {
                    tail = nullptr;
                }
            }
            else {
                previous->next = current->next;

                if (current == tail) {
                    tail = previous;
                }
            }

            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

void LinkedList::print() {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    Node* current = head;

    if (!circular) {
        while (current != nullptr) {
            cout << current->name
                 << " | Cost: $" << current->cost
                 << " | Owner: " << current->owner
                 << endl;

            current = current->next;
        }
    }
    else {
        do {
            cout << current->name
                 << " | Cost: $" << current->cost
                 << " | Owner: " << current->owner
                 << endl;

            current = current->next;

        } while (current != head);
    }
}

void LinkedList::makeCircular() {
    if (head == nullptr) {
        return;
    }

    tail->next = head;
    circular = true;
}

Node* LinkedList::getHead() {
    return head;
}

Node* LinkedList::getTail() {
    return tail;
}

LinkedList::~LinkedList() {
    if (head == nullptr) {
        return;
    }

    if (circular) {
        tail->next = nullptr;
    }

    Node* current = head;

    while (current != nullptr) {
        Node* temp = current;

        current = current->next;

        delete temp;
    }

    head = nullptr;
    tail = nullptr;
}