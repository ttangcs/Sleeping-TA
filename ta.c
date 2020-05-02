/**
 * General structure of the teaching assistant.
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

void *ta_loop(void *param)
{
	int number;
	sem_wait(&students_sem);

	pthread_mutex_lock(&mutex_lock);

	sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);

	if(waiting_students >= 1) {
		waiting_students--;

		help_student(sleep_time);
	}
	pthread_mutex_unlock(&mutex_lock);

	sleep(sleep_time);
	sem_post(&ta_sem);
	printf("I am the TA\n");
	ta_loop((void*)&number);
}
