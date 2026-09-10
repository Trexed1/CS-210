#include <iostream>
#include <vector>
using namespace std;
//iterative binarySearch
int iterativeBinarySearch(vector<int>& a, int target) {
    int low = 0;
    int high = a.size() - 1;
    //tracks the amount of element comparisons 
    int comparisons = 0;

    while (low <= high) {
        comparisons++;
        int mid = (low + high) / 2;
        if (a[mid] == target) { 
            cout << "Comparisons: " << comparisons << endl; 
            cout << "Index: " << mid << endl;
            return mid; }
        //if the target is greater than a[mid], the new low is mid + 1
        else if (a[mid] < target) low = mid + 1;
        //if the target is less than a[mid], the new high index is mid - 1
        else high = mid - 1;
    }
  cout << "Comparisons: " << comparisons << endl; 
  cout << "No index found for " << target << endl;
  return -1;
}

int recursiveBinarySearch(vector<int>& a, int target, int low, int high,int comparisons) {
    //base case: no index is found for target
    if(low > high) {
        cout << "Comparisons: " << comparisons << endl; 
        cout << "No index found for " << target << endl;
        return -1;
    }
    int mid = (high + low) / 2;
    comparisons ++;
    //recursive cases:
    if(a[mid] == target){
        cout << "Comparisons: " << comparisons << endl; 
        cout << "Index: " << mid << endl;
        return mid;
    }
    //if the target is greater than a[mid], the new low is mid + 1
    else if (a[mid] < target) return recursiveBinarySearch(a, target, mid + 1, high, comparisons);
    //if the target is less than a[mid], the new high index is mid - 1
    else return recursiveBinarySearch(a, target, low, mid - 1, comparisons);
}

int linearSearch(vector<int> & a, int target){
    int comparisons = 0;
    for (int i = 0; i < a.size(); ++i){
        comparisons++;
        if(target == a[i]){
            cout << "Comparisons: " << comparisons << endl; 
            cout << "Index: " << i << endl;
            return i;
        }
    }
    cout << "Comparisons: " << comparisons << endl; 
    cout << "No index found for " << target << endl;
    return -1;
}

int main() {
    vector<int> a = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
    int high = a.size() - 1;
    int low = 0, target = 0, comparisons = 0;

    cout << "Test 1: first element" << endl;
    target = a[0];
    cout << "Iterative: " << endl;
    iterativeBinarySearch(a, target);
    cout << "Recursive: " << endl;
    recursiveBinarySearch(a, target, low, high, comparisons);
    cout << "Linear: " << endl;
    linearSearch(a, target);
    cout << "" << endl;

    cout << "Test 2: last element" << endl;
    target = a[high];
    cout << "Iterative: " << endl;
    iterativeBinarySearch(a, target);
    cout << "Recursive: " << endl;
    recursiveBinarySearch(a, target, low, high, comparisons);
     cout << "Linear: " << endl;
    linearSearch(a, target);
    cout << "" << endl;

    cout << "Test 3: middle element:" << endl;
    target = a[(high + low) / 2];
    cout << "Iterative: " << endl;
    iterativeBinarySearch(a, target);
    cout << "Recursive: " << endl;
    recursiveBinarySearch(a, target, low, high, comparisons);
     cout << "Linear: " << endl;
    linearSearch(a, target);
    cout << "" << endl;

    cout << "Test 4: missing value below the range" << endl;
    target = 0;
    cout << "Iterative: " << endl;
    iterativeBinarySearch(a, target);
    cout << "Recursive: " << endl;
    recursiveBinarySearch(a, target, low, high, comparisons);
     cout << "Linear: " << endl;
    linearSearch(a, target);
    cout << "" << endl;

    cout << "Test 5: missing value inside the range" << endl;
    target = 88;
    cout << "Iterative: " << endl;
    iterativeBinarySearch(a, target);
    cout << "Recursive: " << endl;
    recursiveBinarySearch(a, target, low, high, comparisons);
     cout << "Linear: " << endl;
    linearSearch(a, target);
    cout << "" << endl;

}


