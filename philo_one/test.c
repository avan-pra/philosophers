#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_test{
	int yo;
	pthread_mutex_t *mutex;
}				t_test;

void *test1212(void *param)
{
	t_test *hi;
	int wsh;

	hi = (t_test*)param;
	wsh = pthread_mutex_lock(hi->mutex);
	printf("num = %d %d\n", hi->yo, wsh);
	return (NULL);
}

int main(void)
{
	pthread_t thread[5];
	pthread_mutex_t mutex;
	t_test wsh1;
	t_test wsh2;
	int k = 0;

	mutex = (pthread_mutex_t)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
	wsh1.mutex = &mutex;
	wsh1.yo = 1;
	wsh2.mutex = &mutex;
	wsh2.yo = 0;
	pthread_create(&thread[0], NULL, &test1212, &wsh1);
	pthread_create(&thread[1], NULL, &test1212, &wsh2);
	// printf("%d\n", pthread_mutex_lock(&mutex));
	// printf("%d\n", pthread_mutex_lock(&mutex));
	sleep(1);
	return (0);
}
