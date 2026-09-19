#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <random>
#include <string>
using namespace std;

bool isSorted(const std::vector<int>& values){
    if(values.size() == 1) return true;
    if(values.size() == 0) return true;
    for(int i = 1; i < values.size(); ++i){
        if(values[i -1] > values[i] ){
            cout << "Its Not Sorted!" << endl;
            return false; 
        } 
    }
    cout << "Its Sorted!" << endl;
    return true;
}

void printVector(const std::vector<int>& values){
    for(int b : values){
        cout << b << " ";
    }
    cout << '\n';
}
// bubble sort, selection sort, insertion sort, and quicksort from scratch
void bubbleSort(std::vector<int>& values){

    for(int i = 0; i < values.size(); ++i){
        for(int j = 0; j < values.size() - 1 - i; j++){
            if(values[j] > values[j + 1]){
                swap(values[j], values[j + 1]);
            }
        }
    }
}


void selectionSort(std::vector<int>& values){
    for(int i = 0; i < values.size() - 1 ; i++){
        int min = i;
        for(int j = i + 1; j < values.size(); j++){
            if(values[j] < values[min]) min = j;
        }
        swap(values[min], values[i]);
    }
}

void insertionSort(std::vector<int>& values){
    for (int i = 1; i < values.size(); ++i) {
    int key = values[i];
    int j = i - 1;

    while (j >= 0 && values[j] > key) {
        values[j + 1] = values[j];
        --j;
    }

    values[j + 1] = key;
    }
}

int partition(std::vector<int>& values, int low, int high) {
    int pivot = values[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (values[j] < pivot) {
            i++;
            swap(values[i], values[j]);
        }
    }
    swap(values[i + 1], values[high]);
    return i + 1;
}

void quickSort(std::vector<int>& values,int low, int high){
    if (low < high) {
        // pi is partitioning index, values[pi] is now at right place
        int pi = partition(values, low, high);

        // Separately sort elements before partition and after partition
        quickSort(values, low, pi - 1);
        quickSort(values, pi + 1, high);
    }



}

void runBenchmark(const vector<int>& original, string inputType) {
    vector<int> bubbleValues = original;
    vector<int> selectionValues = original;
    vector<int> insertionValues = original;
    vector<int> quickValues = original;

    cout << "\n" << inputType
         << " - Size: " << original.size() << endl;

    //bubble 
    auto start = chrono::steady_clock::now();
    bubbleSort(bubbleValues);
    auto end = chrono::steady_clock::now();
    auto bubbleTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Bubble Sort:    " << bubbleTime << " microseconds" << endl;
    isSorted(bubbleValues);

    //selection 
    start = chrono::steady_clock::now();
    selectionSort(selectionValues);
    end = chrono::steady_clock::now();
    auto selectionTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Selection Sort: " << selectionTime << " microseconds" << endl;
    isSorted(selectionValues);

    //insertion 
    start = chrono::steady_clock::now();
    insertionSort(insertionValues);
    end = chrono::steady_clock::now();
    auto insertionTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Insertion Sort: " << insertionTime << " microseconds" << endl;
    isSorted(insertionValues);

    //quick 
    start = chrono::steady_clock::now();
    quickSort(quickValues, 0, quickValues.size() - 1);
    end = chrono::steady_clock::now();
    auto quickTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Quick Sort:     " << quickTime << " microseconds" << endl;
    isSorted(quickValues);
}
//NOTE: never used random in C++ before, LLM helped me learn the syntax and basics.
vector<int> generateRandomVector(int size) {
    vector<int> values;

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 100000);

    for (int i = 0; i < size; ++i) {
        values.push_back(distribution(generator));
    }

    return values;
}

int main() {
    vector<int> sizes = {500, 1000, 2000};
    for (int size : sizes) {
        //random
        vector<int> randomValues = generateRandomVector(size);
        runBenchmark(randomValues,"Random Input");

        //sorted
        vector<int> sortedValues;
        for (int i = 0; i < size; ++i) {
            sortedValues.push_back(i);
        }
        runBenchmark(sortedValues,"Sorted Input");

        //reverse
        vector<int> reverseValues;
        for (int i = size; i > 0; --i) {
            reverseValues.push_back(i);
        }
        runBenchmark(reverseValues,"Reverse-Sorted Input");
    }

    return 0;
}
