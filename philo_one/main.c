#include "header.h"

void	*print(void *buf)
{
	printf("%s\n", buf);
	return (NULL);
}

static void	philo_run(char **params, int noeat)
{
	pthread_mutex_lock(&mutex);
	char *str1 = "aaaaaa";
	pthread_t p1;

	pthread_create(&p1, NULL, print, (void*)str1);
	pthread_join(p1, NULL);
	printf("1 param: %s\nnoeat = %d\n", params[0], noeat);
	pthread_mutex_unlock(&mutex);
}

int	main (int argc, char **argv)
{
	// number, ttd, tte, tts, nofeat
	pthread_mutex_init(&mutex, NULL);
	if (argc >= 5 && argc <= 6)
		philo_run(argv, argc - 5);
	else
		printf("Incorrect number of arguments\n");
	return (0);
}
