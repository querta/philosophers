#include "header.h"

static int	printmsg(t_phil *ph, t_msg msg)
{
	if (ph->m->dead || !ph->ate)
		return (1);
	pthread_mutex_lock(&ph->m->print);
	printf("%lldms %d ", timedelta(ph->m->start_time), ph->id + 1);
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
	pthread_mutex_unlock(&ph->m->print);
	return (0);
}

static int	eat(t_phil *ph)
{
	if (ph->m->dead || !ph->ate)
		return (1);
	pthread_mutex_lock(ph->left);
	printmsg(ph, FORK);
	pthread_mutex_lock(ph->right);
	printmsg(ph, FORK);
	ph->time = get_time();
	printmsg(ph, EAT);
	ph->ate--;
	msleep(ph->m->tteat);
	pthread_mutex_unlock(ph->left);
	pthread_mutex_unlock(ph->right);
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
		pthread_mutex_lock(&ph->m->mutex);
		if (((int)(timedelta(ph->time)) >= ph->m->ttdie) && !ph->m->dead)
		{
			printmsg(ph, DIED);
			ph->m->dead = 1;
			pthread_mutex_unlock(&ph->m->mutex);
			break ;
		}
		pthread_mutex_unlock(&ph->m->mutex);
		msleep(2);
	}
	return (NULL);
}

static void	*act(void *p)
{
	t_phil	*ph;

	ph = (t_phil *)p;
	if (pthread_create(&ph->monitor, NULL, &monitor, p))
		return ((void *)1);
	if ((ph->id + 1) % 2 == 0)
		msleep(ph->m->tteat);
	while (ph->ate)
	{
		if (eat(ph))
			break ;
		printmsg(ph, THINK);
	}
	return (NULL);
}

int	create_threads(t_main *m)
{
	int			i;
	pthread_t	*threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * m->amount);
	if (!threads)
		return (1);
	i = 0;
	while (i < m->amount)
	{
		m->id = i;
		if (pthread_create(&(threads[i]), NULL, act, (void *)(&m->ph[i])))
			return (1);
		m->ph[i].thread = &threads[i];
		i++;
	}
	i = 0;
	while (i < m->amount)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (0);
}
