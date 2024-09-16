#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// Function to initialize a matrix with random values (double)
void initializeMatrix(double **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = ((double)rand() / RAND_MAX) * 10.0; // Initialize with random values between 0.0 and 10.0
        }
    }
}

// Function to multiply two matrices (double)
void multiplyMatrices(double **first, double **second, double **result, int size) {
    // Loop collapse for i and j
    int ij_size = size * size;
    for (int ij = 0; ij < ij_size; ij++) {
        int i = ij / size;
        int j = ij % size;
        for (int k = 0; k < size; k++) {
            result[i][j] += first[i][k] * second[k][j];
        }
    }
}

// Function to print a matrix (double)
void printMatrix(double **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to calculate elapsed time between two timeval structs
double calculateElapsedTime(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <matrix size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        fprintf(stderr, "Matrix size must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    while(--size){

        struct timeval start, end;
        double elapsed_time;
        double total_time = 0.0;

        // Dynamically allocate memory for matrices
        gettimeofday(&start, NULL);
        double **first = (double **)malloc(size * sizeof(double *));
        double **second = (double **)malloc(size * sizeof(double *));
        double **result = (double **)malloc(size * sizeof(double *));
        for (int i = 0; i < size; i++) {
            first[i] = (double *)malloc(size * sizeof(double));
            second[i] = (double *)malloc(size * sizeof(double));
            result[i] = (double *)malloc(size * sizeof(double));
        }
        gettimeofday(&end, NULL);
        elapsed_time = calculateElapsedTime(start, end);
        //printf("Time taken for memory allocation: %lf seconds\n", elapsed_time);
        total_time += elapsed_time;

        srand(time(NULL)); // Seed for random number generation

        // Initialize matrices with random values
        gettimeofday(&start, NULL);
        initializeMatrix(first, size);
        initializeMatrix(second, size);
        gettimeofday(&end, NULL);
        elapsed_time = calculateElapsedTime(start, end);
        //printf("Time taken for matrix initialization: %lf seconds\n", elapsed_time);
        total_time += elapsed_time;
        

        // Initialize elements of result matrix to 0
        gettimeofday(&start, NULL);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result[i][j] = 0.0;
            }
        }
        gettimeofday(&end, NULL);
        elapsed_time = calculateElapsedTime(start, end);
        //printf("Time taken for result matrix initialization: %lf seconds\n", elapsed_time);
        total_time += elapsed_time;

        // Measure execution time of matrix multiplication
        gettimeofday(&start, NULL);
        multiplyMatrices(first, second, result, size);
        gettimeofday(&end, NULL);
        elapsed_time = calculateElapsedTime(start, end);
        printf("%d,%lf\n",size, elapsed_time);
        total_time += elapsed_time;

        // Free allocated memory
        gettimeofday(&start, NULL);
        for (int i = 0; i < size; i++) {
            free(first[i]);
            free(second[i]);
            free(result[i]);
        }
        free(first);
        free(second);
        free(result);
        gettimeofday(&end, NULL);
        elapsed_time = calculateElapsedTime(start, end);
        //printf("Time taken for memory deallocation: %lf seconds\n", elapsed_time);
        total_time += elapsed_time;

        //printf("Total Time: %lf\n\n",total_time);
    }

    return 0;
}
