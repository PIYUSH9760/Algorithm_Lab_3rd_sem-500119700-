#include <stdio.h>
#include <string.h>
#include <time.h>

void naive_search(char *text, char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);
    for (int i = 0; i <= n - m; i++)
    {
        int j;
        for (j = 0; j < m; j++)
        {
            if (text[i + j] != pattern[j])
            {
                break;
            }
        }
        if (j == m)
        {
            // Pattern found
        }
    }
}

void compute_lps_array(char *pattern, int m, int *lps)
{
    int length = 0;
    lps[0] = 0;
    int i = 1;
    while (i < m)
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else
        {
            if (length != 0)
            {
                length = lps[length - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmp_search(char *text, char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);
    int lps[m];
    compute_lps_array(pattern, m, lps);
    int i = 0, j = 0;
    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }
        if (j == m)
        {
            // Pattern found
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
}

#define PRIME 101

void rabin_karp_search(char *text, char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    for (i = 0; i < m - 1; i++)
    {
        h = (h * 256) % PRIME;
    }
    for (i = 0; i < m; i++)
    {
        p = (256 * p + pattern[i]) % PRIME;
        t = (256 * t + text[i]) % PRIME;
    }
    for (i = 0; i <= n - m; i++)
    {
        if (p == t)
        {
            for (j = 0; j < m; j++)
            {
                if (text[i + j] != pattern[j])
                {
                    break;
                }
            }
            if (j == m)
            {
                // Pattern found
            }
        }
        if (i < n - m)
        {
            t = (256 * (t - text[i] * h) + text[i + m]) % PRIME;
            if (t < 0)
            {
                t = (t + PRIME);
            }
        }
    }
}

void compare_performance(char *text, char *pattern)
{
    clock_t start, end;
    double time_naive, time_kmp, time_rabin_karp;

    // Naive Search
    start = clock();
    naive_search(text, pattern);
    end = clock();
    time_naive = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Naive Search Time: %f seconds\n", time_naive);

    // KMP Search
    start = clock();
    kmp_search(text, pattern);
    end = clock();
    time_kmp = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("KMP Search Time: %f seconds\n", time_kmp);

    // Rabin-Karp Search
    start = clock();
    rabin_karp_search(text, pattern);
    end = clock();
    time_rabin_karp = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Rabin-Karp Search Time: %f seconds\n", time_rabin_karp);
}

int main()
{
    char text[1000];
    char pattern[100];
        printf("Enter the text: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0';

        printf("Enter the pattern: ");
        fgets(pattern, sizeof(pattern), stdin);
        pattern[strcspn(pattern, "\n")] = '\0';

        printf("\nResults for Test Case :\n");
        compare_performance(text, pattern);


    return 0;
}
