#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* entry function to the threads */
void *entry(void *x_void_ptr)
{
	sleep(1);
	printf("Hello World %d\n", x_void_ptr);
	return NULL;
}

int main()
{
	pthread_t myThreadID;
	printf("Before Thread\n");
	pthread_create(&myThreadID, NULL, entry, 2);
	pthread_join(myThreadID, NULL);
	printf("After Thread\m");
	exit(0);
}