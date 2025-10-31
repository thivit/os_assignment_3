/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend)
{
    // this is the conquer step. merge two subarrays into one sorted subarray
    
    // B is temp array
    int i = leftstart;  // left subarray
    int j = rightstart; // right subarray
    int k = leftstart;  // temp array

    // merge subarrays (compare elements)
    while (i <= leftend && j <= rightend)
    {
        if (A[i] < A[j])
        {
            B[k] = A[i];
            i++;
        }
        else
        {
            B[k] = A[j];
            j++;
        }
        k++;
    }

    // copy remaining elements from left then right subarrays
    while (i <= leftend)
    {
        B[k] = A[i];
        i++;
        k++;
    }

    while (j <= rightend)
    {
        B[k] = A[j];
        j++;
        k++;
    }

    int size = rightend - leftstart + 1;
    memcpy(A + leftstart, B + leftstart, size * sizeof(int));
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right)
{
    // base case
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    my_mergesort(left, mid);
    my_mergesort(mid + 1, right);

    merge(left, mid, mid + 1, right);
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void* _args)
{
    struct argument* args = (struct argument*) args;
    int left = args->left;
    int right = args->right;
    int level = args->level;

    if (left >= right)
    {
        free(args);
        return;
    }

    if (level >= cutoff)
    {
        my_mergesort(left, right);
        free(args);
        return;
    }

    // split into subarrays to be handled by different threads
    int mid = left + (right - left) / 2;
    pthread_t left_thread, right_thread;

    struct argument* left_args = buildArgs(left, mid, level + 1);
    struct argument* right_args = buildArgs(mid + 1, right, level + 1);

    pthread_create(&left_thread, NULL, parallel_mergesort, left_args);
    pthread_create(&right_thread, NULL, parallel_mergesort, right_args);

    pthread_join(left_thread, NULL);
    pthread_join(right_thread, NULL);

    merge(left, mid, mid + 1, right);

    free(args);
    return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level)
{
    struct argument* args = malloc(sizeof(struct argument));

    p->left = left;
    p->right = right;
    p->level = level;

    return p;
}