/**
 * General structure of a student.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ta.h"


void *student_loop(void *param)
{
	int number = *((int *)param);
	int sleep_time;

	printf("I am student %d ", number);

	srandom((unsigned)time(NULL));
	sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
	programming(sleep_time);

	pthread_mutex_lock(&mutex_lock);
	sem_getvalue(&ta_sem, &sem_value);
	pthread_mutex_unlock(&mutex_lock);

	if(sem_value > 0) {
		sem_wait(&ta_sem);
		pthread_mutex_lock(&mutex_lock);
		if(waiting_students >= 0 && waiting_students < NUM_OF_SEATS) {
			waiting_student_queue[waiting_students] = number;

			printf("Student %d sits and waits, %d students waiting.\n", student_id[number], *waiting_student_queue);
			waiting_students++;

			pthread_mutex_unlock(&mutex_lock);
			sem_post(&students_sem);

			sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);

			sleep(sleep_time);
		}
		else {
			printf("Seats full\n");

			pthread_mutex_unlock(&mutex_lock);

			printf("Student %d will try again later.", number);

			sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);

			sleep(sleep_time);

			student_loop(&number);
		}
	}
	else {
		sem_post(&students_sem);
	}

	student_loop((void*)&number);
	
	return NULL;
}
