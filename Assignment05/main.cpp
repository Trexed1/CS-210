#include "Assignment05.h"
#include <iostream>

using namespace std;

void checkInsert(string action, bool actual, bool expected,
                 int& steps, int& failures) {
    steps++;
    bool passed = (actual == expected);
    if (!passed) failures++;

    cout << steps << ". " << action << " -> ";
    if (actual) cout << "success";
    else cout << "rejected";
    if (passed) cout << " [PASS]" << endl;
    else cout << " [FAIL]" << endl;
}

void checkRemove(string action, bool actual, int value,
                 bool expected, int expectedValue, int& steps, int& failures) {
    steps++;
    bool passed = (actual == expected && value == expectedValue);
    if (!passed) failures++;

    cout << steps << ". " << action << " -> ";
    if (actual) cout << value;
    else cout << "empty";
    if (passed) cout << " [PASS]" << endl;
    else cout << " [FAIL]" << endl;
}

int main() {
    int totalSteps = 0;
    int failures = 0;

    testStacks(totalSteps, failures);
    testQueues(totalSteps, failures);
    testDeques(totalSteps, failures);

    cout << "\nTOTAL: " << totalSteps << " operations; "
         << failures << " failures" << endl;

    if (failures == 0) return 0;
    return 1;
}
