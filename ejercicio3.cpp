#include <stdio.h>
#include <iostream>
#include "./auxiliary/heap_sort.cpp"

using namespace std;

int main(){

    int* arr;
    int n;
    cin >> n;
    arr = new int[n];
    for(int i = 0; i < n; i++){
        int k;
        cin >> k;
        arr[i] = k;
    }
    heapSort(arr, n);
    for(int i = 0; i < n; i++){
        cout << arr[i] << endl;
    }

    return 0;
}