#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

//WRONG BUT GOOD TRY GO NEXT


int *numbers;

void *summing(void *arg)
{
	int flag = 0;
	int sum = 0;
	static int actual;
	flag = actual;
	while(flag < *(int *)arg)
	{
		sum  += numbers[flag];
		flag++;
	}
	*(int *)arg = sum;
	printf("somma fino a index: %d è = a %d\n",flag, sum);
	actual = flag;
	return arg;
}

int main(int argc, char**argv)
{
	int i=0;
	pthread_t *t = malloc(sizeof(pthread_t) * 2);
	int size = argc;
	numbers = malloc(sizeof(int) * argc);
	
	while(i < argc-1)
	{
		numbers[i] = atoi(argv[i+1]);
		i++;	
	}
	i=0;
	while(i < 2)
	{
		int *a = malloc(sizeof(int) * 1);
		*a = (i+1) * (size/2);
		if(*a == argc-1)
			size++;
		pthread_create(&t[i], NULL, &summing, a);
		i++;
	}
	i = 0;
	int sum = 0;
	while(i < 2)
	{
		int *save;
		pthread_join(t[i], (void **) &save);
		sum += *save;
		free(save);
		i++;
	}
	printf("somma = %d\n", sum);
	free(numbers);
	free(t);

}