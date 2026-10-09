# Assignment05 code guide

Tyler Rex | CS 210 | C++17

## What to run

From `Assignment05/` in the VS Code terminal:

```bash
clang++ -std=c++17 -Wall -Wextra main.cpp -o assignment05
./assignment05
```

The first command builds the program. The second command prints every attempted operation and its checked result. The captured run is in `actual_output.txt`. The final line of that run is `TOTAL: 101 operations; 0 failures`. The executable `assignment05` is a local build product; the source file is `main.cpp`.

## Common interface and error handling

All six structures store `int` values. Insertion functions return `true` when they succeed. The three fixed-capacity array structures return `false` if they are full, without changing their contents. The linked structures have no fixed capacity; allocation failure would be reported by C++ as an exception. Removal functions take `int& value` as an output parameter and return `true` if they removed an item. On an empty structure they return `false` without changing `value`. `isEmpty()` and `size()` let the caller inspect state in constant time.

The array capacity is five so the demonstration can show a full structure without a long test. This is a fixed size, not a resizeable array. `count` is the number of live items. Every array insertion checks `count == CAPACITY` before writing, so there is no out-of-bounds write.

## ArrayStack

`data[5]` holds items from bottom to top, and `count` is also the index of the next free slot. `push` writes at `data[count]` and then increments `count`. `pop` first checks for empty, then decrements `count` and reads `data[count]`. The most recently pushed value is therefore the first removed: last in, first out (LIFO). A rejected push or pop leaves the state unchanged.

## LinkedStack

Each private `Node` stores a value and a pointer to the next node. `head` always points at the top. `push` creates a node whose `next` is the old head, then makes that node the new head. `pop` saves the old head's value, advances `head`, deletes the old node, and decrements `count`. This also gives LIFO order without traversal. The destructor walks the remaining nodes and deletes each one. Copy construction and assignment are disabled so an accidental shallow pointer copy cannot cause two objects to delete the same nodes.

## ArrayQueue

The queue is a circular array. `front` is the index of the oldest item; `count` says how many items exist. `enqueue` writes at `(front + count) % CAPACITY`, which is the next available position after the last item. `dequeue` reads `data[front]`, then advances `front` with `(front + 1) % CAPACITY`. The modulo operation wraps an index from the end of the array to zero. This avoids shifting elements. The oldest item leaves first: first in, first out (FIFO). The test removes 10 and 20, then inserts 60 and 70 into slots that became free, checking wraparound and FIFO order.

## LinkedQueue

Each node has a value and `next`. `head` is the oldest item and `tail` is the newest. `enqueue` attaches a new node after `tail`; when empty, it sets both `head` and `tail` to the new node. `dequeue` removes `head`. If that was the last node, it also sets `tail` to `nullptr`. Maintaining both pointers makes insertion and removal constant time. The destructor deletes any nodes still present. Copying is disabled for the same ownership reason as `LinkedStack`.

## ArrayDeque

A deque allows insertion and removal at both ends. This circular array also uses `front` and `count`. `pushFront` moves `front` backward with `(front + CAPACITY - 1) % CAPACITY` before writing. Adding `CAPACITY` keeps the intermediate value nonnegative. `pushBack` writes at `(front + count) % CAPACITY`. `popFront` reads `front` and moves it forward. `popBack` reads `(front + count - 1) % CAPACITY` and decreases `count`; it does not need to move `front`. Every operation checks for full or empty before changing an index. When the last item is removed, `front` may be any valid index, because the next insertion computes its position from that index and `count == 0`.

## LinkedDeque

Each private node has `previous` and `next` pointers. `head` is the front and `tail` is the back. `pushFront` links a new node before `head`; `pushBack` links one after `tail`. `popFront` moves `head` forward; `popBack` moves `tail` backward. For a one-node deque, removing from either end sets both pointers to `nullptr`. For a larger deque, the new end node's outward pointer is set to `nullptr`, preventing a dangling link. The destructor deletes remaining nodes by following `next`, and copying is disabled to preserve unique ownership.

## Test driver

`checkInsert` compares an insertion's actual Boolean result with the expected result and prints `PASS` or `FAIL`. `checkRemove` also compares a removed value when removal succeeds and verifies that a failed removal leaves the output value unchanged. The `testStack`, `testQueue`, and `testDeque` function templates run the same core sequence against each representation. This makes it easy to see whether array and linked versions obey the same rules. The `bounded` argument adds full-capacity tests for array versions. Local lambdas perform removals before passing the output value to `checkRemove`, avoiding any ambiguity about function-argument evaluation order.

Each test begins with removal from an empty structure, performs at least sixteen attempted insertions/removals, drains the structure, and checks another empty removal. It then checks `isEmpty()` and `size()`. The stack test checks LIFO order. The queue test checks FIFO order and circular wraparound. The deque test mixes front and back operations, including circular wraparound for the array version. `main` creates one object of each class, runs all six tests, prints the operation and failure totals, and exits with status 0 only if every check passes.

## Complexity

Let `n` be the number of stored items and `C = 5` the array capacity.

| Structure | Insertion | Removal | `isEmpty`, `size` | Space |
| --- | --- | --- | --- | --- |
| Array stack | O(1) | O(1) | O(1) | O(C) |
| Linked stack | O(1) | O(1) | O(1) | O(n) |
| Array queue | O(1) | O(1) | O(1) | O(C) |
| Linked queue | O(1) | O(1) | O(1) | O(n) |
| Array deque | O(1) at either end | O(1) at either end | O(1) | O(C) |
| Linked deque | O(1) at either end | O(1) at either end | O(1) | O(n) |

The array operations do not become O(n) in this fixed-capacity design: a full insertion simply returns `false`. A resizeable array could require O(n) for one insertion when it grows and copies items, but this code does not resize. A queue or deque that shifts array elements on removal could also take O(n); the circular indices avoid that. A singly linked deque without a `previous` pointer would need O(n) to find the node before the tail for `popBack`; the doubly linked design avoids it. Destroying a linked structure with `n` remaining nodes is O(n). Printing or otherwise visiting all `n` stored elements would also be O(n), although the test driver only prints each attempted operation.

## Compiler messages and fixes

The requested build completed without compiler errors or warnings. If a future edit causes `use of undeclared identifier`, check spelling and whether the variable is in scope. If it causes `no member named ...`, compare the call with the class's public method name. If it causes `expected ';'`, check the end of the preceding declaration. If a linked-list edit causes a crash after removal, inspect the empty and one-node cases and make sure removed nodes are deleted only once. Rebuild with the exact command above after a fix; `-Wall -Wextra` makes common mistakes visible.
