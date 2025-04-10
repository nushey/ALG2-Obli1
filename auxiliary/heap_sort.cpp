#pragma once

void swap(int *&arr, int x, int y){
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

void siftDown(int*& arr, int pos, int end){
    if(pos > end) return;
    int leftChild = pos * 2+1;
    int rightChild = pos * 2 + 2;
    int swapPos = pos;

    if(leftChild <= end && arr[leftChild] > arr[swapPos]){
        swapPos = leftChild;
    }
    if(rightChild <= end && arr[rightChild] > arr[swapPos]){
        swapPos = rightChild;
    }
    if(swapPos != pos){
        swap(arr, swapPos, pos);
        siftDown(arr, swapPos, end);
    }
}

void heapify(int*& arr, int size){
    int start = (size-1)/2;
    while(start >= 0){
        siftDown(arr, start, size - 1);
        start--;
    }
}

void heapSort(int* arr, int size){

    heapify(arr, size);

    int end = size - 1;
    while(end > 0){
        swap(arr, 0, end);
        end--;
        siftDown(arr, 0, end);
    }
}