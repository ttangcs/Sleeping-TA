/**
 * Simulate a student programming
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void programming(int sleep_time)
{
	printf("programming for %d\n", sleep_time);
	sleep(sleep_time);
}
