#include <iostream>
#include <string>

using namespace std;

// Array structures have a fixed capacity. A failed insertion changes nothing.
class ArrayStack {
private:
    static const int CAPACITY = 5;
    int data[CAPACITY];
    int count;

public:
    ArrayStack() : count(0) {}

    bool push(int value) {
        if (count == CAPACITY) return false;
        data[count++] = value;
        return true;
    }

    bool pop(int& value) {
        if (isEmpty()) return false;
        value = data[--count];
        return true;
    }

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

class LinkedStack {
private:
    struct Node { int value; Node* next; };
    Node* head;
    int count;

public:
    LinkedStack() : head(nullptr), count(0) {}
    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;

    bool push(int value) {
        head = new Node{value, head};
        ++count;
        return true;
    }

    bool pop(int& value) {
        if (isEmpty()) return false;
        Node* old = head;
        value = old->value;
        head = old->next;
        delete old;
        --count;
        return true;
    }

    bool isEmpty() const { return head == nullptr; }
    int size() const { return count; }

    ~LinkedStack() {
        while (head != nullptr) {
            Node* old = head;
            head = head->next;
            delete old;
        }
    }
};

class ArrayQueue {
private:
    static const int CAPACITY = 5;
    int data[CAPACITY];
    int front;
    int count;

public:
    ArrayQueue() : front(0), count(0) {}

    bool enqueue(int value) {
        if (count == CAPACITY) return false;
        data[(front + count) % CAPACITY] = value;
        ++count;
        return true;
    }

    bool dequeue(int& value) {
        if (isEmpty()) return false;
        value = data[front];
        front = (front + 1) % CAPACITY;
        --count;
        return true;
    }

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

class LinkedQueue {
private:
    struct Node { int value; Node* next; };
    Node* head;
    Node* tail;
    int count;

public:
    LinkedQueue() : head(nullptr), tail(nullptr), count(0) {}
    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;

    bool enqueue(int value) {
        Node* node = new Node{value, nullptr};
        if (tail == nullptr) head = node;
        else tail->next = node;
        tail = node;
        ++count;
        return true;
    }

    bool dequeue(int& value) {
        if (isEmpty()) return false;
        Node* old = head;
        value = old->value;
        head = old->next;
        if (head == nullptr) tail = nullptr;
        delete old;
        --count;
        return true;
    }

    bool isEmpty() const { return head == nullptr; }
    int size() const { return count; }

    ~LinkedQueue() {
        while (head != nullptr) {
            Node* old = head;
            head = head->next;
            delete old;
        }
    }
};

class ArrayDeque {
private:
    static const int CAPACITY = 5;
    int data[CAPACITY];
    int front;
    int count;

public:
    ArrayDeque() : front(0), count(0) {}

    bool pushFront(int value) {
        if (count == CAPACITY) return false;
        front = (front + CAPACITY - 1) % CAPACITY;
        data[front] = value;
        ++count;
        return true;
    }

    bool pushBack(int value) {
        if (count == CAPACITY) return false;
        data[(front + count) % CAPACITY] = value;
        ++count;
        return true;
    }

    bool popFront(int& value) {
        if (isEmpty()) return false;
        value = data[front];
        front = (front + 1) % CAPACITY;
        --count;
        return true;
    }

    bool popBack(int& value) {
        if (isEmpty()) return false;
        value = data[(front + count - 1) % CAPACITY];
        --count;
        return true;
    }

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

class LinkedDeque {
private:
    struct Node { int value; Node* previous; Node* next; };
    Node* head;
    Node* tail;
    int count;

public:
    LinkedDeque() : head(nullptr), tail(nullptr), count(0) {}
    LinkedDeque(const LinkedDeque&) = delete;
    LinkedDeque& operator=(const LinkedDeque&) = delete;

    bool pushFront(int value) {
        Node* node = new Node{value, nullptr, head};
        if (head == nullptr) tail = node;
        else head->previous = node;
        head = node;
        ++count;
        return true;
    }

    bool pushBack(int value) {
        Node* node = new Node{value, tail, nullptr};
        if (tail == nullptr) head = node;
        else tail->next = node;
        tail = node;
        ++count;
        return true;
    }

    bool popFront(int& value) {
        if (isEmpty()) return false;
        Node* old = head;
        value = old->value;
        head = old->next;
        if (head == nullptr) tail = nullptr;
        else head->previous = nullptr;
        delete old;
        --count;
        return true;
    }

    bool popBack(int& value) {
        if (isEmpty()) return false;
        Node* old = tail;
        value = old->value;
        tail = old->previous;
        if (tail == nullptr) head = nullptr;
        else tail->next = nullptr;
        delete old;
        --count;
        return true;
    }

    bool isEmpty() const { return head == nullptr; }
    int size() const { return count; }

    ~LinkedDeque() {
        while (head != nullptr) {
            Node* old = head;
            head = head->next;
            delete old;
        }
    }
};

void checkInsert(const string& action, bool actual, bool expected,
                 int& steps, int& failures) {
    ++steps;
    bool pass = actual == expected;
    if (!pass) ++failures;
    cout << steps << ". " << action << " -> "
         << (actual ? "success" : "rejected")
         << " [" << (pass ? "PASS" : "FAIL") << "]\n";
}

void checkRemove(const string& action, bool actual, int value,
                 bool expected, int expectedValue, int& steps, int& failures) {
    ++steps;
    bool pass = actual == expected && value == expectedValue;
    if (!pass) ++failures;
    cout << steps << ". " << action << " -> ";
    if (actual) cout << value;
    else cout << "empty";
    cout << " [" << (pass ? "PASS" : "FAIL") << "]\n";
}

template <typename Stack>
void testStack(const string& name, Stack& stack, bool bounded,
               int& totalSteps, int& failures) {
    int steps = 0;
    int value = -1;
    auto pop = [&](bool expected, int expectedValue = 0) {
        int before = value;
        bool actual = stack.pop(value);
        checkRemove("pop", actual, value, expected,
                    expected ? expectedValue : before, steps, failures);
    };
    cout << "\n" << name << "\n";
    pop(false);
    checkInsert("push 10", stack.push(10), true, steps, failures);
    checkInsert("push 20", stack.push(20), true, steps, failures);
    checkInsert("push 30", stack.push(30), true, steps, failures);
    pop(true, 30);
    checkInsert("push 40", stack.push(40), true, steps, failures);
    checkInsert("push 50", stack.push(50), true, steps, failures);
    checkInsert("push 60", stack.push(60), true, steps, failures);
    if (bounded)
        checkInsert("push 99 while full", stack.push(99), false, steps, failures);
    pop(true, 60);
    pop(true, 50);
    checkInsert("push 70", stack.push(70), true, steps, failures);
    pop(true, 70);
    pop(true, 40);
    pop(true, 20);
    pop(true, 10);
    pop(false);
    if (!stack.isEmpty() || stack.size() != 0) ++failures;
    cout << "Operations: " << steps << "; final size: " << stack.size() << "\n";
    totalSteps += steps;
}

template <typename Queue>
void testQueue(const string& name, Queue& queue, bool bounded,
               int& totalSteps, int& failures) {
    int steps = 0;
    int value = -1;
    auto dequeue = [&](bool expected, int expectedValue = 0) {
        int before = value;
        bool actual = queue.dequeue(value);
        checkRemove("dequeue", actual, value, expected,
                    expected ? expectedValue : before, steps, failures);
    };
    cout << "\n" << name << "\n";
    dequeue(false);
    checkInsert("enqueue 10", queue.enqueue(10), true, steps, failures);
    checkInsert("enqueue 20", queue.enqueue(20), true, steps, failures);
    checkInsert("enqueue 30", queue.enqueue(30), true, steps, failures);
    checkInsert("enqueue 40", queue.enqueue(40), true, steps, failures);
    checkInsert("enqueue 50", queue.enqueue(50), true, steps, failures);
    if (bounded)
        checkInsert("enqueue 99 while full", queue.enqueue(99), false, steps, failures);
    dequeue(true, 10);
    dequeue(true, 20);
    checkInsert("enqueue 60", queue.enqueue(60), true, steps, failures);
    checkInsert("enqueue 70", queue.enqueue(70), true, steps, failures);
    dequeue(true, 30);
    dequeue(true, 40);
    dequeue(true, 50);
    dequeue(true, 60);
    dequeue(true, 70);
    dequeue(false);
    if (!queue.isEmpty() || queue.size() != 0) ++failures;
    cout << "Operations: " << steps << "; final size: " << queue.size() << "\n";
    totalSteps += steps;
}

template <typename Deque>
void testDeque(const string& name, Deque& deque, bool bounded,
               int& totalSteps, int& failures) {
    int steps = 0;
    int value = -1;
    auto popFront = [&](bool expected, int expectedValue = 0) {
        int before = value;
        bool actual = deque.popFront(value);
        checkRemove("popFront", actual, value, expected,
                    expected ? expectedValue : before, steps, failures);
    };
    auto popBack = [&](bool expected, int expectedValue = 0) {
        int before = value;
        bool actual = deque.popBack(value);
        checkRemove("popBack", actual, value, expected,
                    expected ? expectedValue : before, steps, failures);
    };
    cout << "\n" << name << "\n";
    popFront(false);
    checkInsert("pushBack 10", deque.pushBack(10), true, steps, failures);
    checkInsert("pushFront 20", deque.pushFront(20), true, steps, failures);
    checkInsert("pushBack 30", deque.pushBack(30), true, steps, failures);
    popBack(true, 30);
    checkInsert("pushFront 40", deque.pushFront(40), true, steps, failures);
    checkInsert("pushBack 50", deque.pushBack(50), true, steps, failures);
    popFront(true, 40);
    checkInsert("pushBack 60", deque.pushBack(60), true, steps, failures);
    popBack(true, 60);
    checkInsert("pushFront 70", deque.pushFront(70), true, steps, failures);
    if (bounded) {
        checkInsert("pushBack 80", deque.pushBack(80), true, steps, failures);
        checkInsert("pushFront 99 while full", deque.pushFront(99), false, steps, failures);
        popBack(true, 80);
    }
    popFront(true, 70);
    popFront(true, 20);
    popBack(true, 50);
    popBack(true, 10);
    popBack(false);
    if (!deque.isEmpty() || deque.size() != 0) ++failures;
    cout << "Operations: " << steps << "; final size: " << deque.size() << "\n";
    totalSteps += steps;
}

int main() {
    int totalSteps = 0;
    int failures = 0;
    ArrayStack arrayStack;
    LinkedStack linkedStack;
    ArrayQueue arrayQueue;
    LinkedQueue linkedQueue;
    ArrayDeque arrayDeque;
    LinkedDeque linkedDeque;

    testStack("ARRAY STACK", arrayStack, true, totalSteps, failures);
    testStack("LINKED STACK", linkedStack, false, totalSteps, failures);
    testQueue("ARRAY QUEUE", arrayQueue, true, totalSteps, failures);
    testQueue("LINKED QUEUE", linkedQueue, false, totalSteps, failures);
    testDeque("ARRAY DEQUE", arrayDeque, true, totalSteps, failures);
    testDeque("LINKED DEQUE", linkedDeque, false, totalSteps, failures);

    cout << "\nTOTAL: " << totalSteps << " operations; "
         << failures << " failures\n";
    return failures == 0 ? 0 : 1;
}
