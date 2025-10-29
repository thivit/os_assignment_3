/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
	int i = leftstart;
	int j = rightstart;
	int k = leftstart;

	while (i <= leftend && j <= rightend) {
		if (A[i] <= A[j]) {
			B[k++] = A[i++];
		}
		else {
			B[k++] = A[j++];
		}
	}
	while (i <= leftend){
		B[k++] = A[i++];
	}
	while (j <= rightend){
		B[k++] = A[j++];
	}

	memcpy(&A[leftstart], &B[leftstart], sizeof(int) * (rightend - leftstart +1));
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
	if (left >= right) return;

	int mid = left + (right - left) / 2;
	my_mergesort(left, mid);
	my_mergesort(mid + 1, right);

	merge(left, mid, mid+1, right);
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
	struct argument *a = (struct argument *)arg;
	int left = a->left;
	int right = a->right;
	int level = a->level;

	if (left >= right){
		return NULL;
	}
	if (level >= cutoff){
		my_mergesort(left, right);
		return NULL;
	}

	int mid = left + (right-left) / 2;
	pthread_t t1, t2;

	struct argument *a1 = buildArgs(left, mid, level + 1);
	struct argument *a2 = buildArgs(mid + 1, right, level + 1);

	pthread_create(&t1, NULL, parallel_mergesort, a1);
	pthread_create(&t2, NULL, parallel_mergesort, a2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	free(a1);
	free(a2);
	
	merge(left, mid, mid + 1, right);

	return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
	struct argument *p = malloc(sizeof(struct argument));

	p->left = left;
	p->right = right;
	p->level = level;
	return p;
}

