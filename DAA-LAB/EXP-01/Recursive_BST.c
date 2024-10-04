#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SIZES 5

struct Node* insertRecursive(struct Node*, int);  // Prototype for inserting recursively in a binary tree.
struct Node* createNode(int);

// Structure for a node in the binary search tree.
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

int main() {
    // Define the sizes to test
    int sizes[NUM_SIZES] = {50000, 100000, 500000, 1000000, 5000000};

    for (int j = 0; j < NUM_SIZES; j++) {
        int SIZE = sizes[j];
        printf("Inserting %d elements:\n", SIZE);

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

        // Create an empty binary search tree (root node is NULL)
        struct Node* root = NULL;

        start_time = clock(); // Starting the clock to measure time.

        // Insert numbers from the array into the binary search tree recursively
        for (int i = 0; i < SIZE; i++) {
            root = insertRecursive(root, arr[i]);
        }

        end_time = clock();
        total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("Total elapsed time for %d elements is %f seconds\n\n", SIZE, total_time);

        free(arr); // Free the allocated memory for the array
    }

    return 0;
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1); // Exit if memory allocation fails
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node recursively in a binary search tree
struct Node* insertRecursive(struct Node* root, int data) {
    // Base case: If the tree is empty, return the new node as the root
    if (root == NULL) {
        return createNode(data);
    }

    // Recursive case: Traverse the tree to find the correct position
    if (data < root->data) {
        root->left = insertRecursive(root->left, data);  // Insert in the left subtree
    } else if (data > root->data) {
        root->right = insertRecursive(root->right, data); // Insert in the right subtree
    }

    // Return the unchanged root pointer
    return root;
}
