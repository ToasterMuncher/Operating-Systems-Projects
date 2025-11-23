/*
 * Abdullah Almaroof and Julio
 * TCES 430 - Autumn 2025
 * November 22, 2025,
 * Project 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_SIZE 20
#define MAX_TIME 1000
#define MAX_PHASES 5

int numberOfJobs = 1; //Have the first job be job 1
int MAX_JOBS = MAX_SIZE;
int numberOfFinishedJobs = 0;
int allDone=0;

void* cpu_worker_thread(void* arg);
void* io_worker_thread(void* arg);
void* job_submitter_thread(void* arg);

//This struct defines a job and its variables
struct job {

    int jobID;

    // [MAXPHASES][0] = type (0=CPU, 1=IO)
    // [MAXPHASES][1] = duration in milliseconds
    int cpu_and_io_time[MAX_PHASES][2];

    int currentPhase; // Phase types: 0 = CPU phase; 1 = IO phase

    int isCompleted;

};

//This defines the linklist struct we make, it has a pointer to the next data and the data stored in the current node
typedef struct Node {
    struct job *Job;
    struct Node *next;
}Node;

// Defining a Queue is just pointing to rear and front of nodes
struct Queue {

    Node *front;
    Node *rear;
};

void initQueue(struct Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

int isQueueEmpty(struct Queue *q) {
    return (q->front == NULL);
}

void enqueue(struct Queue *q, struct job *job) {

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->Job = job;
    newNode->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

struct job *dequeue(struct Queue *q) {
    if (isQueueEmpty(q)) {
        return NULL;
    }

    Node *temp = q->front;
    struct job *job = temp->Job;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return job;
}

//Threads 0-3 are used to make jobs
//Threads 4-7 are used to handle IOQueue
//Threads 8-15 are used to handle CPU time

//This function will randomly assign CPU and IO times for a job
void timeInit(struct job *x) {
    for (int i = 0; i < MAX_PHASES; i++) {
        //sets if either an IO or CPU job
        //all jobs will always have the first phase be CPU
        if (i == 0) {
            x->cpu_and_io_time[i][0] = 0;
        }
        //Phase types: 0 = CPU phase; 1 = IO phase
        //After first phase, the job can be either IO or CPU in any combination
        else if (i != 0) {
            x->cpu_and_io_time[i][0] = (rand() % 2);
        }
        //sets duration of CPU or IO phase
        x->cpu_and_io_time[i][1] = (rand() % MAX_TIME + 1);

    }
    printf("Job %d initialized | Phase 0: %s (%dms) | Phase 1: %s (%dms) | Phase 2: %s (%dms) | Phase 3: %s (%dms) | Phase 4: %s (%dms)\n",
           x->jobID,
           x->cpu_and_io_time[0][0] == 0 ? "CPU" : "IO", x->cpu_and_io_time[0][1],
           x->cpu_and_io_time[1][0] == 0 ? "CPU" : "IO", x->cpu_and_io_time[1][1],
           x->cpu_and_io_time[2][0] == 0 ? "CPU" : "IO", x->cpu_and_io_time[2][1],
           x->cpu_and_io_time[3][0] == 0 ? "CPU" : "IO", x->cpu_and_io_time[3][1],
           x->cpu_and_io_time[4][0] == 0 ? "CPU" : "IO", x->cpu_and_io_time[4][1]);
}


//Threads 0-3 are used to make jobs
//Threads 4-7 are used to handle IOQueue
//Threads 8-15 are used to handle CPU time

//We will have total of 16 (0-15) threads
pthread_t threads[16];

// At the top, outside any function
struct Queue ReadyQueue;
struct Queue IOWaitQueue;
struct Queue FinishedQueue;

pthread_mutex_t ready_mutex;
pthread_mutex_t io_mutex;
pthread_mutex_t finished_mutex;
pthread_mutex_t jobID_mutex;
pthread_mutex_t finishedalljobs_mutex;

int main(void) {

    // Remove next 6 lines to output to terminal instead of file

    int fd = open("Project3 Abdullah and Julio.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open output file");
        return 1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);


    srand(time(NULL)); // Initialize random number generator

    //this sets the Front and Rear node pointers to NULL for all three queues
    initQueue(&ReadyQueue);
    initQueue(&IOWaitQueue);
    initQueue(&FinishedQueue);

    //This initializes all the locks we will use for the critical sections we have
    pthread_mutex_init(&ready_mutex, NULL);
    pthread_mutex_init(&io_mutex, NULL);
    pthread_mutex_init(&finished_mutex, NULL);
    pthread_mutex_init(&jobID_mutex, NULL);
    pthread_mutex_init(&finishedalljobs_mutex, NULL);

    // Start the 16 threads we will use

    //These four are to make jobs and handle finished queue
    pthread_create(&threads[0], NULL, &job_submitter_thread, NULL);
    pthread_create(&threads[1], NULL, &job_submitter_thread, NULL);
    pthread_create(&threads[2], NULL, &job_submitter_thread, NULL);
    pthread_create(&threads[3], NULL, &job_submitter_thread, NULL);

    //These four are to handle the IOQueue
    pthread_create(&threads[4], NULL, &io_worker_thread, NULL);
    pthread_create(&threads[5], NULL, &io_worker_thread, NULL);
    pthread_create(&threads[6], NULL, &io_worker_thread, NULL);
    pthread_create(&threads[7], NULL, &io_worker_thread, NULL);

    //These eight are to handle CPUQueue
    pthread_create(&threads[8], NULL, &cpu_worker_thread, NULL);
    pthread_create(&threads[9], NULL, &cpu_worker_thread, NULL);
    pthread_create(&threads[10], NULL, &cpu_worker_thread, NULL);
    pthread_create(&threads[11], NULL, &cpu_worker_thread, NULL);
    pthread_create(&threads[12], NULL, &cpu_worker_thread, NULL);
    pthread_create(&threads[13], NULL, &cpu_worker_thread, NULL);
    pthread_create(&threads[14], NULL, &cpu_worker_thread, NULL);
    pthread_create(&threads[15], NULL, &cpu_worker_thread, NULL);

    // Wait for all threads to finish
    for (int i = 0; i < 16; i++) {
        pthread_join(threads[i], NULL);
    }

    // Cleanup
    pthread_mutex_destroy(&ready_mutex);
    pthread_mutex_destroy(&io_mutex);
    pthread_mutex_destroy(&finished_mutex);
    pthread_mutex_destroy(&jobID_mutex);
    pthread_mutex_destroy(&finishedalljobs_mutex);

    return 0;


}


void* cpu_worker_thread(void* arg) {

    // Check ready queue
    // Process CPU phases
    // Move jobs to next queue

    // This code runs in the new thread
    while (allDone == 0) {

        pthread_mutex_lock(&ready_mutex); // Lock the queue

        if (ReadyQueue.front != NULL) {
            struct job *Job = dequeue(&ReadyQueue);
            pthread_mutex_unlock(&ready_mutex);

            int jobID = Job->jobID; // Get the jobID
            int phase = Job->currentPhase; // Get the current phase job is in
            int totalTime = Job->cpu_and_io_time[phase][1]; // Get the total time it will take to accomplish

            printf("Job %d is executing in CPU, it will take %d milliseconds\n",jobID, totalTime ); //Print that we are executing
            usleep(totalTime * 1000); // Complete execution of program
            printf("Job %d is completed in CPU\n", jobID);

            if (Job->currentPhase == 4) {
                Job->isCompleted = 1;
                printf("Job %d is set to completed\n", jobID);
                pthread_mutex_lock(&finished_mutex);
                enqueue(&FinishedQueue, Job);
                printf("Job %d is queued to Finished Queue\n", jobID);
                pthread_mutex_unlock(&finished_mutex);
            }

            else {
                Job->currentPhase = phase + 1; // Update the current phase of program
                if (Job->cpu_and_io_time[phase + 1][0] == 0) {
                    pthread_mutex_lock(&ready_mutex);
                    enqueue(&ReadyQueue, Job);
                    printf("Job %d is queued to Ready Queue\n", jobID);
                    pthread_mutex_unlock(&ready_mutex);
                }
                else if (Job->cpu_and_io_time[phase + 1][0] == 1) {
                    pthread_mutex_lock(&io_mutex);
                    enqueue(&IOWaitQueue, Job);
                    printf("Job %d is queued to IO Queue\n", jobID);
                    pthread_mutex_unlock(&io_mutex);
                }

            }
        }
        else {
            pthread_mutex_unlock(&ready_mutex);
            usleep(3 * 1000 * 100); //Wait 300ms
        }
    }
    return NULL;
}

void* io_worker_thread(void* arg) {
    // Check I/O wait queue
    // Process I/O phases
    // Move jobs to next queue

    while (allDone == 0) {

        pthread_mutex_lock(&io_mutex); // Lock the queue

        if (IOWaitQueue.front != NULL) {
            struct job *Job = dequeue(&IOWaitQueue);
            pthread_mutex_unlock(&io_mutex);

            int jobID = Job->jobID; // Get the jobID
            int phase = Job->currentPhase; // Get the current phase job is in
            int totalTime = Job->cpu_and_io_time[phase][1]; // Get the total time it will take to accomplish

            printf("Job %d is executing in IO, it will take %d milliseconds\n",jobID, totalTime ); //Print that we are executing
            usleep(totalTime * 1000); // Complete execution of program
            printf("Job %d is completed in IO\n", jobID);

            if (Job->currentPhase == (MAX_PHASES-1)) {
                Job->isCompleted = 1;
                printf("Job %d is set to completed\n", jobID);
                pthread_mutex_lock(&finished_mutex);
                enqueue(&FinishedQueue, Job);
                printf("Job %d is queued to Finished Queue\n", jobID);
                pthread_mutex_unlock(&finished_mutex);
            }

            else {
                Job->currentPhase = phase + 1; // Update the current phase of program
                if (Job->cpu_and_io_time[phase + 1][0] == 0) {
                    pthread_mutex_lock(&ready_mutex);
                    enqueue(&ReadyQueue, Job);
                    printf("Job %d is queued to Ready Queue\n", jobID);
                    pthread_mutex_unlock(&ready_mutex);
                }
                else if (Job->cpu_and_io_time[phase + 1][0] == 1) {
                    pthread_mutex_lock(&io_mutex);
                    enqueue(&IOWaitQueue, Job);
                    printf("Job %d is queued to IO Queue\n", jobID);
                    pthread_mutex_unlock(&io_mutex);
                }

            }
        }
        else {
            pthread_mutex_unlock(&io_mutex);
            usleep(3 * 1000 * 100); //Wait 300ms
        }
    }
    return NULL;
}

void* job_submitter_thread(void* arg) {
    // Create new job
    // Check finished queue
    // Sleep 300 milliseconds

    while (allDone == 0) {
        if (numberOfJobs <= MAX_JOBS) {
            struct job *job = (struct job *)malloc(sizeof(struct job));

            pthread_mutex_lock(&jobID_mutex); // Lock global variable numberOfJobs, which is used to give an accurate JobID for each created job
            job->jobID = numberOfJobs;
            numberOfJobs ++;
            pthread_mutex_unlock(&jobID_mutex);

            timeInit(job);
            job->isCompleted = 0;
            job->currentPhase = job->cpu_and_io_time[0][0];
            printf("New Job Created with Job ID: %d, it's current phase is: %d\n", job->jobID, job->currentPhase);

            pthread_mutex_lock(&ready_mutex);
            enqueue(&ReadyQueue, job);
            printf("Job %d has been added to CPU Queue\n", job->jobID);
            pthread_mutex_unlock(&ready_mutex);
            free(job);
        }

        pthread_mutex_lock(&finished_mutex);
        if (!isQueueEmpty(&FinishedQueue)) {
            struct job *finishedJob = dequeue(&FinishedQueue);
            pthread_mutex_unlock(&finished_mutex);

            printf("Job %d has finished and been dequeued from Finish Queue\n", finishedJob->jobID);
            free(finishedJob);

            pthread_mutex_lock(&finishedalljobs_mutex);
            numberOfFinishedJobs++;
            printf("DEBUG: Finished %d / %d jobs\n", numberOfFinishedJobs, MAX_JOBS);
            pthread_mutex_unlock(&finishedalljobs_mutex);
        } else {
            pthread_mutex_unlock(&finished_mutex);
        }


        if (numberOfFinishedJobs >= MAX_JOBS) {
            printf("All Jobs Finished\n");
            allDone = 1;
        }
        usleep(3 * 1000 * 100); //Wait 300ms
    }
    return NULL;
}
