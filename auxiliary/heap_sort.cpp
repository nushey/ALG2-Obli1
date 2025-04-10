#pragma once

void swap(int *arr, int x, int y){
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

void siftDown(int* arr, int pos, int end) {
    while (pos * 2 + 1 <= end) {
        int leftChild = pos * 2 + 1;
        int rightChild = pos * 2 + 2;
        int swapPos = pos;

        if (leftChild <= end && arr[leftChild] > arr[swapPos]) {
            swapPos = leftChild;
        }
        if (rightChild <= end && arr[rightChild] > arr[swapPos]) {
            swapPos = rightChild;
        }
        if (swapPos == pos) {
            break;
        }
        swap(arr, swapPos, pos);
        pos = swapPos;
    }
}

void heapify(int* arr, int size) {
    for (int start = (size - 1) / 2; start >= 0; --start) {
        siftDown(arr, start, size - 1);
    }
}
void heapSort(int* arr, int size) {
    heapify(arr, size);

    for (int end = size - 1; end > 0; --end) {
        swap(arr, 0, end);
        siftDown(arr, 0, end - 1);
    }
}