#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // swap arr[i] and arr[minIndex]
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            // swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // swap arr[i+1] and arr[high]
    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void merge(vector<int>& arr, int left, int middle, int right) {
    vector<int> leftArr(middle - left + 1);
    vector<int> rightArr(right - middle);

    for (int i = 0; i < leftArr.size(); i++) {
        leftArr[i] = arr[left + i];
    }

    for (int i = 0; i < rightArr.size(); i++) {
        rightArr[i] = arr[middle + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < leftArr.size()) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < rightArr.size()) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

void countingSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal+1);
    vector<int> output(arr.size());

    for (int i = 0; i < arr.size(); i++) {
        count[arr[i]]++;
    }

    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i-1];
    }

    for (int i = arr.size()-1; i >= 0; i--) {
        output[count[arr[i]]-1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

void radixSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());

    for (int exp = 1; maxVal/exp > 0; exp *= 10) {
        vector<int> output(arr.size());
        vector<int> count(10);

        for (int i = 0; i < arr.size(); i++) {
            count[(arr[i]/exp)%10]++;
        }

        for (int i = 1; i < count.size(); i++) {
            count[i] += count[i-1];
        }

        for (int i = arr.size()-1; i >= 0; i--) {
            output[count[(arr[i]/exp)%10]-1] = arr[i];
            count[(arr[i]/exp)%10]--;
        }

        for (int i = 0; i < arr.size(); i++) {
            arr[i] = output[i];
        }
    }
}

int main() {
    // Open input file (input*xy*.txt) where x is 1 for unsorted and 2 for nearly sorted and y is for size, from 1 to 6
    ifstream inputFile;
    inputFile.open("input11.txt");

    // Read numbers from file
    vector<int> numbers;
    int num;
    while (inputFile >> num) {
        numbers.push_back(num);
    }


    //Function calls

    //bubbleSort(numbers);
    //insertionSort(numbers);
    //selectionSort(numbers);
    //quickSort(numbers, 0, numbers.size() - 1);
    //mergeSort(numbers, 0, numbers.size() - 1);
    //countingSort(numbers);
    radixSort(numbers);


    // Close input file
    inputFile.close();

    /*Output sorted numbers
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;*/

    return 0;
}
