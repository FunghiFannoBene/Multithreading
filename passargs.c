#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

void *rolldice(void *args)
{
	int resx = rand() % 6 +1 * *(int *)args;
	int *res = malloc(1 * sizeof(int));
	printf("sono thread : %d e ho tirato il numero : %d\n", *(int *)args, resx);
	*res = resx;
	return res;
}

int main()
{
	pthread_t t1[5];
	int *res;
	 struct timeval tv;
    gettimeofday(&tv, NULL);

    unsigned long long milliseconds = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;

    srand(milliseconds);
	int i = 0;
	while(i<4)
	{
		int *a = malloc(sizeof(int) *1);
		*a = i;
		if(pthread_create(&(t1[i]), NULL, &rolldice, a)!= 0)
			return 0;
		i++;
	}
	i=0;
	while(i<4)
	{
		pthread_join(t1[i], (void **) &res);
		printf("dichiarato dal thread N: %d , numero : %d, sono uguale?\n", i ,*res);
		free(res);
		i++;
	}
}