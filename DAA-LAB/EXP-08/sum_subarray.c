#include <stdio.h>

void sum_of_subsets(int set[], int subset[], int n, int target, int sum, int index, int subsetSize) {
    // If the sum equals the target, print the subset
    if (sum == target) {
        printf("{ ");
        for (int i = 0; i < subsetSize; i++) {
            printf("%d ", subset[i]);
        }
        printf("}\n");
        return;
    }

    // If the sum exceeds the target or index is out of bounds, return
    if (sum > target || index == n) {
        return;
    }

    // Include the current element in the subset
    subset[subsetSize] = set[index];
    sum_of_subsets(set, subset, n, target, sum + set[index], index + 1, subsetSize + 1);

    // Exclude the current element and move to the next one
    sum_of_subsets(set, subset, n, target, sum, index + 1, subsetSize);
}

int main() {
    int n, target;

    // Take input for the size of the set
    printf("Enter the number of elements in the set: ");
    scanf("%d", &n);

    int set[n];
    int subset[n];

    // Take input for the elements of the set
    printf("Enter the elements of the set:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &set[i]);
    }
    printf("Enter the target sum: ");
    scanf("%d", &target);

    printf("Subsets with sum %d are:\n", target);
    sum_of_subsets(set, subset, n, target, 0, 0, 0);

    return 0;
}
