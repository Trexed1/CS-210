Assignment 01: 2Sum and Complexity
Overview:
You are given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

This assignment implements two approaches to the Two Sum problem in C++17:
- Brute-force using nested loops
- Hash-based lookup using `std::unordered_map`

Files
- main.cpp — implementation and test cases

Testing
The program includes:
- the required instructor-provided test
- a basic test
- duplicate-value test
- negative-number test
- endpoint test

Complexity
- Brute Force: O(n^2) time, O(1) extra space
- Hash Approach: O(n) expected time, O(n) extra space