# Assignment 06: Passwords and Hash Tables

This C++17 program stores five users in a hash table and tests their logins.

## Build and run

In the `Assignment06` folder, run:

```sh
clang++ -std=c++17 -Wall -Wextra main.cpp HashTable.cpp -o assignment06
./assignment06
```

`HashTable.h` declares the table, `HashTable.cpp` implements it, and `main.cpp` runs the examples. The output shows collisions, a resize, successful and failed logins, and removal. Each check prints `PASS` or `FAIL`.

The password hash is for class practice only. Do not use this program for real accounts.
