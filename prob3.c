#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
int i;

int is_prime(int num) {
    int i;
    for (i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int count_prime(int x, int y) {
    int count = 0;
    for ( i = x; i <= y; i++) {
        if (is_prime(i)) {
            count++;
        }
    }
    return count;
}

int main(int argc, char** argv) {
    int p, rank;
    int x, y, r, a, b;
    int count, total_count;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Enter the lower bound : ");
        scanf("%d", &x);
        printf("Enter the upper bound : ");
        scanf("%d", &y);
    }

    start_time = MPI_Wtime();

    if (rank == 0) {
        r = (y - x) / p;
        for ( i = 1; i < p; i++) {
            a = x + i * r;
            b = (i == p - 1) ? y : a + r - 1;
            MPI_Send(&a, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        a = x;
        if (p == 1) {
    b = y;
} else {
    b = x + r - 1;
}
    } else {
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    local_count = count_prime(a, b);

    if (rank == 0) {
        total_count = count;
        for ( i = 1; i < p; i++) {
            MPI_Recv(&count, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_count += count;
        }
    } else {
        MPI_Send(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Total count of primes between %d and %d = %d\n", x, y, total_count-1);
        printf("Execution time = %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();

    return 0;
}
