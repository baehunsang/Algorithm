#include <stdio.h>
typedef struct {
    int* arr;
    int size;
}heap;
typedef heap* Heap;
void swap(int* element1, int* element2);
void Heapify(Heap heap, int index) { //Top to Down 
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;
    int largest = index;
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
        Heapify(heap, largest);   // reculsive action, untile last level Heapify(arr, largest);
    }
}
int main() {
	int arr[] = { 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
    Heap heap = (Heap)malloc(sizeof(heap));
    (heap->size) = 10;
    (heap->arr) = arr;
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    Heapify(heap, 1);
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int* element1, int* element2) {
    int tmp;
    tmp = *element1;
    *element1 = *element2;
    *element2 = tmp;
}
