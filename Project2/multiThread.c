/*
 * Julio Anacleto | Abdullah Almaroof
 * October 27th, 2025
 * Project 2 - Single thread application of matrix dot product
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 2000

typedef struct {
	int** matrixA;		// First input matrix
	int** matrixB;		// Second input matrix
	int** matrixDot;	// Output matrix
	int startRow;		// Starting row for this thread
	int endRow;		// Ending row for this thread exclusive
	int size;		// Matrix dimension (2000)
} ThreadData;

// Threaded dot product function
void *threadDotProduct(void *arg) {
	ThreadData *data = (ThreadData*) arg;

	// Compute assigned section of matrix
	for (int i = data->startRow; i < data->endRow; i++) {
		for (int j = 0; j < data->size; j++) {
			long sum = 0;
			for (int k = 0; k < data->size; k++) {
				sum += data->matrixA[i][k] * data->matrixB[k][j];
			}
			data->matrixDot[i][j] = (int) sum;
		}
	}
	//printf("Thread Done\n");
	return NULL;
}

int main(int argc, char* argv[]) {

	struct timespec start, end;
	double elapsedTime;

	int numThreads;

	// Check if user provided number of threads
	if (argc != 2) {
		printf("Usage: %s <number_of_threads>\n", argv[0]);
		return 1;
	}

	// Convert string argument to integer
	numThreads = atoi(argv[1]);

	// Validate input
	if (numThreads <= 0 || numThreads > SIZE) {
		printf("Invalid number of threads. Must be between 1 and %d\n", SIZE);
		return 1;
	}

	printf("Using %d threads\n", numThreads);

        // Allocate memory for matrixs
        int** matrixA =  malloc(SIZE * sizeof(int*));
        int** matrixB =  malloc(SIZE * sizeof(int*));
	int** matrixDot =  malloc(SIZE * sizeof(int*));
        for (int i = 0; i < SIZE; i++) {
                matrixA[i] = malloc(SIZE * sizeof(int));
                matrixB[i] = malloc(SIZE * sizeof(int));
		matrixDot[i] = malloc(SIZE * sizeof(int));
        }

        // Initialize two input  matrixs with values
        int counter = 0;
        for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                        matrixA[i][j] = counter;
                        matrixB[i][j] = counter++;
                }
        }

	// Create thread structures
	pthread_t threads[numThreads];
	ThreadData threadData[numThreads];

	// Begin clock
	clock_gettime(CLOCK_MONOTONIC, &start);

	// Divide rows between threads
	int rowsPerThread = SIZE / numThreads;
	for (int i = 0; i < numThreads; i++) {
		threadData[i].matrixA = matrixA;
		threadData[i].matrixB = matrixB;
		threadData[i].matrixDot = matrixDot;
		threadData[i].startRow = i * rowsPerThread;
		threadData[i].endRow = (i == numThreads - 1) ? SIZE : (i + 1) * rowsPerThread;
		threadData[i].size = SIZE;

		// Now that we have the necessary data for a thread, we can now create it and send it to run the operations
		if(pthread_create(&threads[i], NULL, threadDotProduct, (void *) &threadData[i]) != 0) {
			perror("Failed to create thread");
			return 1;
		}
	}

	// Wait for all threads to complete
	for (int i = 0; i < numThreads; i++) {
		pthread_join(threads[i], NULL);
	}

	// End Clock
	clock_gettime(CLOCK_MONOTONIC, &end);

	// Display time elapsed
	elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
	printf("Execution time: %f seconds\n", elapsedTime);

        // Display Array (Used for debugging)
        /*
	printf("Matrix multiplication complete\n");
	for (int i = 0; i < SIZE; i++) {
                printf("[ ");
                for (int j = 0; j < SIZE; j++) {
                        printf("%d ", matrixDot[i][j]);
                }
                printf("]\n");
        }
	*/

        // Free allocated memory
	for (int i = 0; i < SIZE; i++) {
		free(matrixA[i]);
		free(matrixB[i]);
		free(matrixDot[i]);
	}
	free(matrixA);
	free(matrixB);
	free(matrixDot);

        return 0;
}

