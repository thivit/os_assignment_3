#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "mergesort.h"

int *A;
int *B;

// 0 = false, 1 = true
int is_sorted(int* arr, int n)
{
    int i = 0;
    for (i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1]) return 0;
    }
    return 1;
}

void print_array(int* arr, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void test_mergesort(int* input, int* expected, int n)
{
    A = (int *) malloc(sizeof(int) * n);
    B = (int *) malloc(sizeof(int) * n);

    memcpy(A, input, sizeof(int) * n);

    printf("Input: ");
    print_array(A, n);

    my_mergesort(0, n - 1);

    printf("Sorted: ");
    print_array(A, n);

    assert(is_sorted(A, n));
    printf("\033[0;32mTest passed!\033[0m\n\n");

    free(A);
    free(B);
}

int main(int argc, char** argv)
{
    printf("Testing mergesort...\n");
    printf("--------------- Test 1 -----------------\n");

    int test1[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
    int expected1[] = { 1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9 };
    test_mergesort(test1, expected1, 11);

    printf("----------------- Test 2 -----------------\n");
    
    int test2[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int expected2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    test_mergesort(test2, expected2, 10);

    printf("----------------- Test 3 -----------------\n");
    int test3[] = { -5, -3, -1, 0, 2, 4, 6, 8, 10 };
    int expected3[] = { -5, -3, -1, 0, 2, 4, 6, 8, 10 };
    test_mergesort(test3, expected3, 10);

    printf("----------------- Test 4 -----------------\n");
    int test4[] = { 1 };
    int expected4[] = { 1 };
    test_mergesort(test4, expected4, 1);

    printf("----------------- Test 5 -----------------\n");
    int test5[] = { };
    int expected5[] = { };
    test_mergesort(test5, expected5, 0);

    return 0;
}