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
	// initialise iterators.
	int i = leftstart;
	int j = rightstart;
	int k = leftstart;

	// add elements to array B in order.
	while (i <= leftend && j <= rightend)
	{
		if (A[i] <= A[j])
		{
			B[k] = A[i];
			k++;
			i++;
		}
		else
		{
			B[k] = A[j];
			k++;
			j++;
		}
	}

	// add rest of the elements.
	while (i <= leftend)
	{
		B[k] = A[i];
		k++;
		i++;
	}
	while (j <= leftend)
	{
		B[k] = A[j];
		k++;
		j++;
	}

	// copy into array A.
	size_t arraySize = (rightend - leftstart + 1) * sizeof(int);
	memcpy(A + leftstart, B + leftstart, arraySize);
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right)
{
	// return if single element in array.
	if (left >= right) return;

	// divide into two subarrays.
	int mid = left + (left + right) / 2;
	my_mergesort(left, mid);
	my_mergesort(mid + 1, right);

	// merge subarrays.
	merge(left, mid, mid + 1, right);
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

