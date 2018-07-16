#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* entry function to the threads */
void *entry(void *x_void_ptr)
{
	if (x_void_ptr != -1) {
		sleep(1);
		printf("Spawning thread from inside the thread %d\n", x_void_ptr);
		pthread_t myThreadID2;
		pthread_create(&myThreadID2, NULL, entry, -1);
		pthread_join(myThreadID2, NULL);
	}
	else {
		printf("Inside double thread  %d\n", x_void_ptr);
	}
	return NULL;
}

int main()
{
	pthread_t myThreadID;
	printf("Before Thread\n");
	pthread_create(&myThreadID, NULL, entry, 1234);
	pthread_join(myThreadID, NULL);
	printf("After Thread\n");
	exit(0);
}
