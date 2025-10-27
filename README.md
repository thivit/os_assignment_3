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
