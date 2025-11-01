# Operating Systems Assignment 3 - Concurrency
## Group 67
Authors: 
- Thivinesh Thanabalan
- Duc Duy Bao Nguyen
- Edwin Chen-Desailly

## Overview
This program outputs the time taken for a random array of numbers to be 
sorted using a multi-threaded merge sort algorithm. It takes the
following arguments:

- size:     the intended size of the random array.
- cutoff:   level at which to switch to serial sorting.
- seed:     the random seed used to generate the array.

## Manifest
```
.
├─ Makefile/            # build rules.
├─ mergesort.c          # implementation of the merge sort functions.
├─ mergersort.h         # function, struct, and global var declarations.
├─ test-mergesort.c     # calls the merge sort with arguments for testing.
└─ README.md            # information about the project.
```
## Building the project
```bash
make
./test-mergesort <size> <cutoff> <seed>
```
## Features and usage
- Parallel merge sort: spawns up to two threads per recursion level.
- Controllable depth: cutoff determines when to switch to serial sorting.
- No race conditions: disjoint subranges + pthread_join before merging.
- Reproducible tests: same seed guarantees the same generated array.

## Testing
- Before implementing the parallel version, proper unit testing of the sequential merge sort
- Uses C assert.h with multiple test cases, including edge cases

## Reflection
- I think understanding the recursion helped with the merge sort initially--basically that the algorithm divides the entire array into single elements first, then merges them all up bit by bit

- The parallelism is not too complicated (having done PDC last semester, its not completely new), we simply replace recursive calls with thread creation up to a certain core count

- One thing that occured to me is that with this naive implementation, the work is not split completely equally. For example, at the first level of recursion, we split the original array into halves, with 2 child threads handling each half. Then, the next pair of threads handles the next two halves etc. To fully optimise it, we could split the original array into equal parts depending on the cutoff parameter, but thats probably beyond the scope of the assignment.
