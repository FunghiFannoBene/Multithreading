#include <pthread.h>
#include <stdio.h>

int creator = 0;

void *routine(void* mutex)
{
	int i = 0;
	while(i < 1000000)
	{
		pthread_mutex_lock(mutex);
		creator++;
		pthread_mutex_unlock(mutex);
		i++;
	}
	printf("i : %d, creator: %d\n", i, creator);
}

int main()
{
	pthread_t t[4];
	int i = 0;
	pthread_mutex_t mutex_t1;
	pthread_mutex_init(&mutex_t1, NULL);
	while(i<4)
	{
		if(pthread_create(&(t[i]), NULL, &routine , &mutex_t1) != 0)
		{
			printf("error\n");
			return 0;
		}
		printf("thread created %d\n", i);
		i++;
	}
	i=0;
	while(i<4)
	{
		if(pthread_join(t[i], NULL) != 0)
		{
			printf("error\n");
			return 0;
		}
		printf("thread joined %d\n", i);
		i++;
	}
}