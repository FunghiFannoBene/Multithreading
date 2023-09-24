#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

void *rolldice(void *args)
{
	int resx = rand() % 6 +1;
	int *res = malloc(1* sizeof(int));
	*res = resx;
	return res;
}

int main()
{
	pthread_t t1[5];
	int *res;
	 struct timeval tv;
    gettimeofday(&tv, NULL);

    // Converti il tempo in millisecondi to represent the total time in milliseconds, and hence the multiplication 
    unsigned long long milliseconds = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
	/*
	By using 1000LL, you're ensuring the arithmetic is done using 64-bit integers, 
	avoiding potential overflows and keeping the arithmetic consistent and safe for very large values of tv.tv_sec.
	*/
    // Usa i millisecondi come seme
    srand(milliseconds);
	int i = 0;
	while(i<4)
	{
		if(pthread_create(&(t1[i]), NULL, &rolldice, NULL)!= 0)
			return 0;
		i++;
	}
	i=0;
	while(i<4)
	{
		pthread_join(t1[i], (void **) &res);
		printf("numero : %d, dichiarato dal thread N: %d\n", *res, i);
		free(res);
		i++;
	}
}