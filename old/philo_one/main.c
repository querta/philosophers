#include "header.h"

static int	init_philo(t_main *m)
{
	int	i;

	i = 0;
	m->ph = (t_phil *)malloc(m->amount * sizeof(t_phil));
	if (!m->ph)
		return (1);
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
	return (0);
}

static int	check_args(char **argv, t_main *m)
{
	if (argv[5])
		m->eat_num = ft_atoi(argv[5]);
	if (m->amount <= 0)
		ft_putendl_fd("Bad number of philosophers", 2);
	else if (argv[5] && m->eat_num < 1)
		ft_putendl_fd("Nobody ate. Try times to eat > 0 or blank", 2);
	else if (m->ttdie < 60 || m->ttsleep < 60 || m->tteat < 60)
		ft_putendl_fd("Time to die, sleep or eat should be > 60ms", 2);
	else
		return (1);
	return (0);
}

static int	struct_init(char **argv, t_main *m)
{
	int	i;

	m->dead = 0;
	m->id = 0;
	m->amount = ft_atoi(argv[1]);
	m->ttdie = ft_atoi(argv[2]);
	m->tteat = ft_atoi(argv[3]);
	m->ttsleep = ft_atoi(argv[4]);
	m->eat_num = -1;
	if (!check_args(argv, m))
		return (1);
	m->forks = (pthread_mutex_t *)malloc(m->amount * sizeof(pthread_mutex_t));
	if (pthread_mutex_init(&m->mutex, NULL) || \
		pthread_mutex_init(&m->print, NULL))
		return (2);
	if (init_philo(m) || !m->forks)
		return (1);
	i = 0;
	while (i < m->amount)
	{
		if (pthread_mutex_init(&(m->forks[i++]), NULL))
			return (2);
	}
	m->start_time = get_time();
	return (0);
}

static void	clear_mem(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->amount)
		pthread_mutex_destroy(&(m->forks[i++]));
	pthread_mutex_destroy(&(m->print));
	pthread_mutex_destroy(&(m->mutex));
	if (m->forks)
		free(m->forks);
	if (m->ph)
		free(m->ph);
}

int	main(int argc, char **argv)
{
	t_main	*m;

	if (argc >= 5 && argc <= 6)
	{
		m = (t_main *)malloc(sizeof(t_main));
		if (!m)
			return (1);
		if (!struct_init(argv, m))
		{
			if (create_threads(m))
				return (1);
			clear_mem(m);
			free(m);
			return (EXIT_SUCCESS);
		}
		free(m);
	}
	else
		ft_putendl_fd("Incorrect number of arguments", 2);
	return (EXIT_FAILURE);
}
