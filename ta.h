/**
 * Header file for sleeping TA
 */

#include <pthread.h>
#include <semaphore.h>

// the maximum time (in seconds) to sleep
#define MAX_SLEEP_TIME	5

// number of maximum waiting students
#define MAX_WAITING_STUDENTS	3

// number of potential students
#define NUM_OF_STUDENTS		5

// number of available seats
#define NUM_OF_SEATS	3

// the numeric id of each student
int student_id[NUM_OF_STUDENTS];

// student function prototype
void *student_loop(void *param);

// ta function prototype
void *ta_loop(void *param);

// simulate programming
void programming(int sleeptime);

// simulate helping a student
void help_student(int sleeptime);

//Create semaphore
sem_t students_sem;

sem_t ta_sem;

pthread_mutex_t mutex_lock;

int waiting_students;
int sem_value;
int waiting_student_queue[MAX_WAITING_STUDENTS];

int sleep_time;