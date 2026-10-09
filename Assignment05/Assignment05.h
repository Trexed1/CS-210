#ifndef ASSIGNMENT05_H
#define ASSIGNMENT05_H

#include <string>

using namespace std;

// These functions print one operation and compare it with the expected result.
void checkInsert(string action, bool actual, bool expected,
                 int& steps, int& failures);
void checkRemove(string action, bool actual, int value,
                 bool expected, int expectedValue, int& steps, int& failures);

// Each function demonstrates the array and linked versions of one ADT.
void testStacks(int& totalSteps, int& failures);
void testQueues(int& totalSteps, int& failures);
void testDeques(int& totalSteps, int& failures);

#endif
