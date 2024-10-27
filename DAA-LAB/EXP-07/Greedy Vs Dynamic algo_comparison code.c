#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEMS 100

// Structure to hold items
typedef struct {
    int value;
    int weight;
} Item;

// Greedy algorithm for 0/1 Knapsack
int greedyKnapsack(Item items[], int n, int capacity) {
    int totalValue = 0;

    // Sort items based on value/weight ratio using Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((double)items[j].value / items[j].weight < (double)items[j + 1].value / items[j + 1].weight) {
                Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        }
    }

    return totalValue;
}

// Dynamic Programming algorithm for 0/1 Knapsack
int knapsackDP(Item items[], int n, int capacity) {
    int dp[n + 1][capacity + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = (items[i - 1].value + dp[i - 1][w - items[i - 1].weight] > dp[i - 1][w]) ? 
                           items[i - 1].value + dp[i - 1][w - items[i - 1].weight] : 
                           dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

// Function to generate random datasets
void generateDataset(Item items[], int n) {
    for (int i = 0; i < n; i++) {
        items[i].weight = rand() % 50 + 1; // Weight between 1 and 50
        items[i].value = rand() % 100 + 1;  // Value between 1 and 100
    }
}

void runAnalysis(int sizes[], int testCount, int capacity) {
    Item items[MAX_ITEMS];

    for (int i = 0; i < testCount; i++) {
        generateDataset(items, sizes[i]);

        clock_t start, end;

        // Greedy Knapsack
        start = clock();
        int greedyResult = greedyKnapsack(items, sizes[i], capacity);
        end = clock();
        double greedyTime = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Dynamic Programming Knapsack
        start = clock();
        int dpResult = knapsackDP(items, sizes[i], capacity);
        end = clock();
        double dpTime = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Output the results
        printf("Dataset size %d:\n", sizes[i]);
        printf("Greedy Result: %d,     Time: %f seconds\n", greedyResult, greedyTime);
        printf("DP Result: %d,         Time: %f seconds\n", dpResult, dpTime);
        printf("\n");
    }
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    // Dataset sizes
    int sizes[] = {5, 10, 20, 30, 50};
    int testCount = sizeof(sizes) / sizeof(sizes[0]);
    int capacity = 100; // Set a constant capacity for all tests

    runAnalysis(sizes, testCount, capacity);

    return 0;
}
