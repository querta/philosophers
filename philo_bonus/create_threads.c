#include "header.h"

static int	printmsg(t_phil *ph, t_msg msg)
{
	if (ph->m->dead || !ph->ate)
		return (1);
	sem_wait(ph->m->print);
	if (!ph->m->dead)
	{
		printf("%llums %d ", \
			(unsigned long long)timedelta(ph->m->start_time), ph->id + 1);
		if (msg == FORK)
			printf("has taken a fork\n");
		else if (msg == EAT)
			printf("is eating\n");
		else if (msg == SLEEP)
			printf("is sleeping\n");
		else if (msg == THINK)
			printf("is thinking\n");
		else if (msg == DIED)
			printf("died\n");
	}
	sem_post(ph->m->print);
	return (0);
}

static int	eat(t_phil *ph)
{
	if (ph->m->dead || !ph->ate)
		return (1);
	sem_wait(ph->m->forks);
	printmsg(ph, FORK);
	sem_wait(ph->m->forks);
	printmsg(ph, FORK);
	ph->time = get_time();
	printmsg(ph, EAT);
	ph->ate--;
	msleep(ph->m->tteat);
	sem_post(ph->m->forks);
	sem_post(ph->m->forks);
	printmsg(ph, SLEEP);
	msleep(ph->m->ttsleep);
	return (0);
}

static void	*monitor(void *p)
{
	t_phil	*ph;

	ph = (t_phil *)p;
	pthread_detach(ph->monitor);
	ph->time = get_time();
	msleep(50);
	while (ph->ate)
	{
		sem_wait(ph->m->status);
		if (((int)(timedelta(ph->time)) > ph->m->ttdie) && !ph->m->dead)
		{
			printmsg(ph, DIED);
			ph->m->dead = 1;
			sem_post(ph->m->status);
			break ;
		}
		sem_post(ph->m->status);
		msleep(1);
	}
	return (NULL);
}

static void	*act(t_phil	*ph)
{
	if (pthread_create(&ph->monitor, NULL, &monitor, (void *)ph))
		return ((void *)1);
	if ((ph->id + 1) % 2 == 0)
		msleep(ph->m->tteat);
	while (ph->ate)
	{
		if (ph->m->dead || eat(ph))
			break ;
		printmsg(ph, THINK);
	}
	return (NULL);
}

static void kill_all(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->amount)
	{
		kill(m->ph[i++].pid, SIGKILL);
	}
}

int	create_threads(t_main *m)
{
	int			i;
	int status;
	// pthread_t	*threads;

	// threads = (pthread_t *)malloc(sizeof(pthread_t) * m->amount);
	// if (!threads)
	// 	return (1);
	i = 0;
	while (i < m->amount)
	{
		m->id = i;
		if (m->ph[i].pid == -1)
			m->ph[i].pid = fork();
		if (m->ph[i].pid < 0)
		{
			kill_all(m);
			return (1);
		}
		else if (m->ph[i].pid == 0)
		{
			act(m->ph);
		}
		// m->ph[i].thread = &threads[i];
		i++;
	}
	i = 0;
	// kill_all(m);
	while (i < m->amount)
	{
		if (wait(&status) == -1)
			return (1);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
				kill_all(m);
			else if (WEXITSTATUS(status) == EXIT_FAILURE)
			{
				kill_all(m);
				return (EXIT_FAILURE);
			}
		}
	}
	// free(threads);
	return (0);
}
