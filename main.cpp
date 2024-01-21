#include <vector>
#include <iostream>
using namespace std;

int binarySearch(vector<double> &x, int start, int end, double key) {
//prelimiinary stuff: O(1)
    while (start <= end) {

        //loop body: O(1)
        int middle = (start + end) / 2;
        if (x[middle] == key) {
            return middle;
        }

        if (key < x[middle]) {
            end = middle - 1;
        }
        else
            start = middle + 1;
    }
    return -1; // O(1)
}

int recursiveSearch(vector<double> &A, int start, int end, double key) {
    if (start >= end) {
        return -1;
    }
    else {
    int middle = (start + end) / 2;
    if (key > A[middle]) {
        return recursiveSearch(A, middle + 1, end, key);
    }
    else if (key < A[middle]) {
        return recursiveSearch(A, start, middle - 1, key);
    }
    if (key == A[middle]) {
        return middle;
    }
    }
}

int main() {
    vector<double> x;
    x.push_back(1);
    x.push_back(4);
    x.push_back(34);
    x.push_back(45);
    x.push_back(67);

    cout << binarySearch(x, 0, x.size(), 0) << endl;
    cout << recursiveSearch(x, 0, x.size(), 67);

}