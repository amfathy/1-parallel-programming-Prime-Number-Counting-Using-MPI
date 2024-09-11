# Parallel Prime Number Counting Using MPI

## Overview

This program demonstrates how to count prime numbers in a given range using MPI for parallel processing. The range is divided among multiple processes, and each process counts the prime numbers in its segment. The results are then combined by the master process to determine the total count of prime numbers in the range.

## Compilation

To compile the program, use the following command:
```bash
mpicc -o prime_count prime_count.c
