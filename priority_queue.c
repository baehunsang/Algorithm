#include <stdio.h>
#include<stdlib.h>

#define Data int

typedef struct {
    Data* arr;
    int size;
    int capacity;
}heap;
typedef heap* Heap;

void swap(Data* element1, Data* element2);
int parent(int index);

void Heapify(Heap heap, int index);
void BuildQueue(Heap heap);
void Insert(Heap heap, Data input);
int HeapIncreaseKey(Heap heap, int index, Data key);
Data HeapExtractMax(Heap heap);
Data HeapMax(Heap heap);


int main() {
    Heap queue = (Heap)malloc(sizeof(heap));
    BuildQueue(queue);
    int indicate =1;
    Data data;
    while (1) {
        printf("Enter the data\n");
        scanf("%d", &data);
        Insert(queue, data);
        printf("End?\n");
        scanf("%d", &indicate);
        if (!indicate) {
            break;
        }
    }
    while(queue->size > 0) {
        printf("Max: %d\n", HeapExtractMax(queue));
    }
}

void swap(Data* element1, Data* element2) {
    int tmp;
    tmp = *element1;
    *element1 = *element2;
    *element2 = tmp;
}

void Heapify(Heap heap, int index) { //Top to Down 
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;
    int largest = index;                   //Making max-heap
    if (leftIndex <= (heap->size) - 1 &&
        heap->arr[leftIndex] > heap->arr[index]) {
        largest = leftIndex;
    } // compare left node
    if (rightIndex <= (heap->size) - 1 &&
        heap->arr[rightIndex] > heap->arr[largest]) {
        largest = rightIndex;
    }// compare right node
    if (largest != index) {
        swap(&heap->arr[index], &heap->arr[largest]); // swap
        Heapify(heap, largest);   // reculsive action, untile last level
    }
}

void BuildQueue(Heap heap) {
    heap->size = 0;
    heap->capacity = 1;
    (heap->arr) = (Data*)malloc(sizeof(Data) * (heap->capacity));
}

void Insert(Heap heap, Data key) {
    if ((heap->size) ==(heap->capacity)) {
        heap->capacity += 2;
        heap->arr = (Data*)realloc(heap->arr, sizeof(Data) * (heap->capacity));
    }
    heap->size++;
    memset(&(heap->arr[(heap->size)-1]),0, sizeof(Data));
    heap->arr[(heap->size) - 1] = -9999;
    HeapIncreaseKey(heap, (heap->size) -1, key);
}
int HeapIncreaseKey(Heap heap, int index, Data key) {
    if (key < heap->arr[index]) {
        return 0;
    }
    heap->arr[index] = key;
  
    while (index>0 && heap->arr[parent(index)] < heap->arr[index]){  //compare 함수 정의 필요
        swap(&(heap->arr[index]), &(heap->arr[parent(index)]));
        index = parent(index);
    }
    return 1;
}

Data HeapExtractMax(Heap heap) {
    if (heap->size <0) {
        printf("Error: Heap underflow");
        return;
    }
    Data max = heap->arr[0];
    heap->arr[0] = heap->arr[(heap->size) - 1];
    heap->size--;
    Heapify(heap, 0);
    return max;
}

Data HeapMax(Heap heap) {
    return heap->arr[0];
}

int parent(int index) {
    if (index % 2 == 0) {
        return (index / 2) - 1;
    }
    else {
        return index / 2;
    }
}