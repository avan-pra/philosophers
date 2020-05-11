#include <pthread.h>
#include <stdio.h>

typedef struct test
{
	int i;
	//pthread_mutex_t *mutex;
}				p_test;


void *test1212(void *t)
{
	p_test *yo;

	yo = (p_test*)t;
	//pthread_mutex_lock(yo->mutex);
	printf("%d\n", yo->i);
	//pthread_mutex_unlock(yo->mutex);
}

int main(void)
{
	pthread_t thread[5];
	pthread_mutex_t mutex;
	p_test test;
	int k = 0;

	//pthread_mutex_init(&(mutex), NULL);
	while (k <= 4)
	{
		test.i = k;
		//test[k].mutex = &mutex;
		pthread_create(&thread[k], NULL, &test1212, &test);
		
		//pthread_join(thread[test.i], NULL);
		++k;
	}
	while (k + 1)
	{
		pthread_join(thread[k], NULL);
		--k;
	}
}
