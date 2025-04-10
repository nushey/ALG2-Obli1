#include <stdio.h>
#include <iostream>
#include "./auxiliary/heap_sort.cpp"

using namespace std;

int main(){

    ios::sync_with_stdio(false); // sin esto demoraba 70s en vez de 10s
    cin.tie(0); // sin esto demoraba 70s en vez de 10s
    cout.tie(0); // sin esto demoraba 70s en vez de 10s
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
        cout << arr[i] << '\n';
    }

    return 0;
}