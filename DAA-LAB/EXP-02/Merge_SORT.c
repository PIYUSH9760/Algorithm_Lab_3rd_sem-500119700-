#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SIZES 5

void mergeSort(int arr[], int beg, int end); // Prototype for mergeSort function.
void merge(int arr[], int beg, int mid, int end);

int main() {
    // Define the sizes to test
    int sizes[NUM_SIZES] = {50000, 100000, 500000, 1000000, 5000000};

    for (int j = 0; j < NUM_SIZES; j++) {
        int SIZE = sizes[j];
        printf("Sorting %d elements:\n", SIZE);

        clock_t start_time;
        clock_t end_time;
        double total_time;

        // Initialize the array to store random numbers
        int *arr = (int *)malloc(SIZE * sizeof(int));
        if (arr == NULL) {
            fprintf(stderr, "Memory allocation failed!\n");
            return 1; // Exit if memory allocation fails
        }

        // Seed the random number generator
        srand(time(0));

        // Generate random numbers and store them in the array
        for (int i = 0; i < SIZE; i++) {
            arr[i] = rand();
        }

        start_time = clock();

        mergeSort(arr, 0, SIZE - 1); // Implementing Merge Sort.

        end_time = clock(); // Ending the clock here after merge sort is complete.

        total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // Measuring the time taken.
        printf("Total elapsed time for %d elements is %f seconds\n\n", SIZE, total_time);

        free(arr); // Free the allocated memory for the array
    }

    return 0;
}

void merge(int arr[], int beg, int mid, int end) { // Function to merge two halves.
    int i = beg, j = mid + 1, index = beg, k;
    int *temp = (int *)malloc((end - beg + 1) * sizeof(int)); // Temporary array for merging
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1); // Exit if memory allocation fails
    }

    while ((i <= mid) && (j <= end)) { // Merge the two halves
        if (arr[i] < arr[j]) {
            temp[index - beg] = arr[i]; // Store in temp
            i++;
        } else {
            temp[index - beg] = arr[j]; // Store in temp
            j++;
        }
        index++;
    }

    // Copy remaining elements from the left half
    while (i <= mid) {
        temp[index - beg] = arr[i];
        i++;
        index++;
    }

    // Copy remaining elements from the right half
    while (j <= end) {
        temp[index - beg] = arr[j];
        j++;
        index++;
    }

    // Copy sorted elements back to the original array
    for (k = beg; k <= end; k++) {
        arr[k] = temp[k - beg];
    }

    free(temp); // Free the temporary array
}

void mergeSort(int arr[], int beg, int end) { // Function to sort using merge sort
    if (beg < end) {
        int mid = beg + (end - beg) / 2;

        mergeSort(arr, beg, mid); // Sort first half
        mergeSort(arr, mid + 1, end); // Sort second half

        merge(arr, beg, mid, end); // Merge the sorted halves
    }
}
