#include "header.h"

//void	*print(void *buf)
//{
//	printf("%s\n", buf);
//	return (NULL);
//}

void init_philo(t_main *m)
{
	int i;

	i = 0;
	m->ph = (t_phil *)malloc(m->amount * sizeof(t_phil));
	while (i < m->amount)
	{
		m->ph[i].id = i;
		m->ph[i].ate = m->eat_num;
		m->ph[i].m = m;
		m->ph[i].left = &m->forks[i];
		if (m->ph[i].id == m->amount - 1)
			m->ph[i].right = &m->forks[0];
		else
			m->ph[i].right = &m->forks[i + 1];
		i++;
	}
}

static void	struct_init(char **argv, t_main *m)
{
	int i;

	m->dead = 0;
	m->id = 0;
	m->amount = ft_atoi(argv[1]);
	m->ttdie = ft_atoi(argv[2]);
	m->tteat = ft_atoi(argv[3]);
	m->ttsleep = ft_atoi(argv[4]);
	m->eat_num = -1;
	if (argv[5])
		m->eat_num = ft_atoi(argv[5]);
	m->forks = (pthread_mutex_t *)malloc(m->amount * sizeof(pthread_mutex_t));
	pthread_mutex_init(&m->mutex, NULL); 
	pthread_mutex_init(&m->print, NULL); 
	init_philo(m);
	i = 0;
	while (i < m->amount)
		pthread_mutex_init(&(m->forks[i++]), NULL);
	m->start_time = get_time();
}

//static void	philo_run(char **params, int noeat)
//{
//	pthread_mutex_lock(&mutex);
//	char *str1 = "aaaaaa";
//	pthread_t p1;
//
//	pthread_create(&p1, NULL, print, (void*)str1);
//	pthread_join(p1, NULL);
//	printf("1 param: %s\nnoeat = %d\n", params[0], noeat);
//	pthread_mutex_unlock(&mutex);
//}

int	main(int argc, char **argv)
{
	t_main *m;

	m = (t_main *)malloc(sizeof(t_main));
	// number, ttd, tte, tts, nofeat
//	pthread_mutex_init(&mutex, NULL);
//	struct_init(argv, argc, m);
	if (argc >= 5 && argc <= 6)
	{
		struct_init(argv, m);
		if (m->ttdie < 60 || m->ttsleep < 60 || m->tteat < 60)
			return (printf("Time to die, Time to sleep, Time to eat shoul be > 60ms\n"));
		// create_philo(m);
		create_threads(m);
		// int i = 0;
		// while (i < m->amount)
		// {
		// 	pthread_join(*m->ph[i].thread, NULL);
		// 	i++;
		// }
	}
	else
	{
		printf("Incorrect number of arguments\n");
		return (1);
	}
	return (0);
}

//  make re && ./philo_one 5 100 10 50 5
//  make re && ./philo_one 5 200 60 60 2
//  make re && ./philo_one 5 800 200 200 7
