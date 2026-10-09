# Assignment05 code guide

Tyler Rex | CS 210 | C++17

## Build and run in VS Code

Open the VS Code terminal in `Assignment05/`, then run:

```bash
clang++ -std=c++17 -Wall -Wextra main.cpp Stack.cpp Queue.cpp Deque.cpp -o assignment05
./assignment05
```

All four `.cpp` files are needed. The first command builds one program named `assignment05`. The second runs it. The actual captured run is in `actual_output.txt` and ends with `TOTAL: 101 operations; 0 failures`.

## File layout

- `Assignment05.h` declares the five functions that are shared between files. A declaration tells the compiler a function exists; its body is in a `.cpp` file. The `#ifndef`, `#define`, and `#endif` lines keep the header from being included twice in the same compilation unit.
- `Stack.cpp` defines `ArrayStack` and `LinkedStack`, then demonstrates both in `testStacks`.
- `Queue.cpp` defines `ArrayQueue` and `LinkedQueue`, then demonstrates both in `testQueues`.
- `Deque.cpp` defines `ArrayDeque` and `LinkedDeque`, then demonstrates both in `testDeques`.
- `main.cpp` defines the small result-checking functions and calls the three demonstration functions.

There are no templates, `auto` variables, or lambdas. The repeated test calls are intentional: each step says exactly which operation is being tested and what result is expected.

## How results are reported

Every insertion returns a `bool`: `true` means the value was added, and `false` means a fixed array was already full. Every removal returns a `bool` and has an `int& value` parameter. The `&` means the function can place the removed number into the caller's variable. If the structure is empty, removal returns `false` without changing `value`. The test sets `value` to `-1` before an expected empty removal to check that rule.

`checkInsert` compares the actual and expected `bool` values. `checkRemove` also compares the returned number (or checks that `-1` stayed unchanged when empty). Each prints `PASS` or `FAIL` and increases the operation count. `main` prints the total and returns 0 if every check passed, or 1 if any failed. This exit code makes a failed test visible to the terminal.

## Stack.cpp

A stack removes the most recently inserted item first. This is last in, first out (LIFO).

`ArrayStack` has `data[5]` and `count`. `count` tells how many array positions are occupied. `push` first checks whether `count` is 5, then writes at `data[count]` and increases `count`. `pop` first checks whether `count` is 0, then decreases `count` and reads that position. Decreasing before reading returns the top value.

`LinkedStack` uses a `Node` with `value` and `next`. `head` points to the top node. `push` allocates a new node, points it to the old head, and makes it the new head. `pop` saves the head value, moves `head` to the next node, deletes the old node, and decreases `count`. The destructor deletes any nodes left when the object goes out of scope.

`testStacks` tries an empty pop, mixes pushes and pops, checks LIFO order, fills the array stack and rejects one extra push, drains both stacks, and tries another empty pop. Each stack has at least 16 operations.

## Queue.cpp

A queue removes the oldest item first. This is first in, first out (FIFO).

`ArrayQueue` has `data[5]`, `front`, and `count`. `front` is the array index of the oldest item. `enqueue` calculates the next open index as `(front + count) % 5`, writes there, and increases `count`. `dequeue` reads `data[front]`, moves `front` to `(front + 1) % 5`, and decreases `count`. `%` is the remainder operator; it wraps an index back to 0 after 4. This avoids moving all the other values.

`LinkedQueue` uses singly linked nodes plus `head` and `tail`. `head` is the oldest item; `tail` is the newest. `enqueue` links a new node after `tail`. When the queue was empty, it sets both pointers to the new node. `dequeue` removes `head`; if that was the last node, it also sets `tail` to `nullptr`. The destructor deletes remaining nodes.

`testQueues` checks empty handling, five insertions, array overflow, FIFO removals, and circular wraparound: after removing 10 and 20, it adds 60 and 70 into reusable array positions. Each queue has at least 16 operations.

## Deque.cpp

A deque (double-ended queue) permits insertion and removal at both the front and the back.

`ArrayDeque` uses `data[5]`, `front`, and `count`. `pushFront` moves `front` one position backward with `(front + 5 - 1) % 5`, then writes. Adding 5 prevents a negative index before `%`. `pushBack` writes at `(front + count) % 5`. `popFront` reads `front` and moves it forward. `popBack` reads `(front + count - 1) % 5` and decreases `count`. Each checks full or empty first. When the last item is removed, the next insertion still works because `count` is 0.

`LinkedDeque` uses nodes with `previous` and `next` pointers. `head` is the front and `tail` is the back. `pushFront` and `pushBack` attach a new node at the chosen end. `popFront` and `popBack` detach and delete the node at the chosen end. When the last node is removed, both `head` and `tail` become `nullptr`. When nodes remain, the new end's outward pointer becomes `nullptr`. The destructor deletes nodes left in the deque.

`testDeques` mixes operations at both ends, checks empty removals, wraps the array indices, and checks array overflow. Each deque has at least 16 operations.

## Complexity

Let `n` be the number of stored items and `C = 5` the array capacity.

- Array stack: `push`, `pop`, `isEmpty`, and `size` are O(1). Space is O(C).
- Linked stack: `push`, `pop`, `isEmpty`, and `size` are O(1). Space is O(n).
- Array queue: `enqueue`, `dequeue`, `isEmpty`, and `size` are O(1). Space is O(C).
- Linked queue: `enqueue`, `dequeue`, `isEmpty`, and `size` are O(1). Space is O(n).
- Array deque: all four end operations, `isEmpty`, and `size` are O(1). Space is O(C).
- Linked deque: all four end operations, `isEmpty`, and `size` are O(1). Space is O(n).

The fixed array operations never become O(n): when full, insertion returns `false` instead of resizing. If we chose a growing array, one insertion could take O(n) to copy items. A queue that shifted array elements after every removal could take O(n), but the circular array avoids shifting. A singly linked deque could take O(n) to find the node before its tail, but the doubly linked deque has a `previous` pointer. Deleting `n` leftover linked nodes in a destructor is O(n).

## Compiler errors and fixes

The requested build completed without errors or warnings. If you compile only `main.cpp`, the linker will report missing definitions for `testStacks`, `testQueues`, and `testDeques`; adding all three implementation files to the compile command fixes that. If you accidentally `#include` a `.cpp` file and also compile it separately, you can get duplicate-definition errors; include only `Assignment05.h`. A message such as `no member named 'push'` usually means a method name was mistyped. A message such as `expected ';'` usually points to a missing semicolon near the previous declaration. After any change, rebuild with the command at the top of this guide.

The linked classes are used as separate objects and are not copied in this program. Copying one with C++'s default copy behavior would copy its pointers, which would be unsafe for owning linked nodes. Avoid copying these objects unless you later implement a proper copy constructor and assignment operator.
