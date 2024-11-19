#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SIZES 5

void swap(int* a, int* b);        // Function to swap two elements
int partition(int arr[], int low, int high);  // Partition function for Quick Sort
void quickSort(int arr[], int low, int high); // Quick Sort function

int main() {
    // Define different array sizes
    int sizes[NUM_SIZES] = {50000, 100000, 500000, 1000000, 5000000};

    // Iterate over each size and perform Quick Sort
    for (int j = 0; j < NUM_SIZES; j++) {
        int SIZE = sizes[j];
        printf("Sorting %d elements:\n", SIZE);

        clock_t start_time, end_time;
        double total_time;

        // Initialize the array to store random numbers
        int* arr = (int*)malloc(SIZE * sizeof(int));
        if (!arr) {
            printf("Memory allocation failed!\n");
            return -1;
        }

        // Seed the random number generator
        srand(time(0));

        // Generate random numbers and store them in the array
        for (int i = 0; i < SIZE; i++) {
            arr[i] = rand();  // Generates random numbers between 0 and RAND_MAX
        }

        // Start measuring time
        start_time = clock();

        // Call the Quick Sort function
        quickSort(arr, 0, SIZE - 1);

        // End measuring time
        end_time = clock();
        total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        // Print elapsed time
        printf("Total elapsed time is %.6f seconds\n\n", total_time);

        // Free dynamically allocated memory
        free(arr);
    }

    return 0;
}

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Taking the last element as pivot
    int i = (low - 1);  // i is the index of the smaller element

    // Reorder elements in the array such that elements smaller than the pivot are on the left
    // and elements greater than the pivot are on the right
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;  // Increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }

    // Swap pivot element with the element at i + 1 so that pivot is in the correct position
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);  // Return the partition index
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Get partition index
        quickSort(arr, low, pi - 1);  // Recursively sort the left subarray
        quickSort(arr, pi + 1, high);  // Recursively sort the right subarray
    }
}
