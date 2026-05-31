#include <stdio.h>

#define MAX 100

// Function to swap two numbers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// This function maintains the min heap property
// It assumes left and right subtrees are already heaps
void heapify(int heap[], int n, int i) {
    int smallest = i;          // Assume current index is smallest
    int left = 2 * i + 1;      // Left child index
    int right = 2 * i + 2;     // Right child index

    // Check if left child is smaller than current smallest
    if (left < n && heap[left] < heap[smallest]) {
        smallest = left;
    }

    // Check if right child is smaller than current smallest
    if (right < n && heap[right] < heap[smallest]) {
        smallest = right;
    }

    // If smallest is not the current node, swap and continue heapifying
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, n, smallest);
    }
}

// Function to build a min heap from an array
void buildHeap(int heap[], int n) {
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

// Function to remove and return the minimum element from the heap
int extractMin(int heap[], int *n) {
    // If heap is empty
    if (*n <= 0) {
        printf("Heap is empty\n");
        return -1;
    }

    // Minimum element is always at the root in a min heap
    int minValue = heap[0];

    // Replace root with the last element
    heap[0] = heap[*n - 1];

    // Reduce heap size
    (*n)--;

    // Restore min heap property
    heapify(heap, *n, 0);

    return minValue;
}

// Function to display heap elements
void displayHeap(int heap[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

// Heap sort using min heap
void heapSort(int arr[], int n) {
    int sorted[MAX];
    int size = n;

    // First convert array into min heap
    buildHeap(arr, size);

    // Repeatedly extract minimum and store it in sorted array
    for (int i = 0; i < n; i++) {
        sorted[i] = extractMin(arr, &size);
    }

    // Copy sorted elements back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = sorted[i];
    }
}

int main() {
    int heap[MAX] = {40, 10, 30, 50, 20, 60};
    int n = 6;

    printf("Original array: ");
    displayHeap(heap, n);

    // Build min heap from the given array
    buildHeap(heap, n);

    printf("Min Heap: ");
    displayHeap(heap, n);

    // Extract the minimum element from the heap
    int minElement = extractMin(heap, &n);

    printf("Extracted minimum element: %d\n", minElement);

    printf("Heap after extraction: ");
    displayHeap(heap, n);

    // Sort the remaining heap elements
    heapSort(heap, n);

    printf("Heap Sort result: ");
    displayHeap(heap, n);

    return 0;
}