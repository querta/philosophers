#include "header.h"

void printmsg(t_phil *ph, t_msg msg)
{
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
}

void eat(t_phil *ph)
{
	pthread_mutex_lock(ph->left);
	printmsg(ph, FORK);
	pthread_mutex_lock(ph->right);
	printmsg(ph, FORK);
	// pthread_mutex_lock(&ph->m->mutex);
	ph->time = get_time();
	printmsg(ph, EAT);
	ph->ate--;
	// pthread_mutex_unlock(&ph->m->mutex);
	msleep(ph->m->tteat);
	// usleep(200000);
	pthread_mutex_unlock(ph->left);
	pthread_mutex_unlock(ph->right);
	printmsg(ph, SLEEP);
	msleep(ph->m->ttsleep);
}

void *monitor(void *p)
{
	t_phil *ph;
	
	ph = (t_phil *)p;
	pthread_detach(ph->monitor);
	while (ph->ate)
	{
		pthread_mutex_lock(&ph->m->mutex);
		if ((int)(get_time() - ph->time) < ph->m->ttdie)
		{
			ph->m->dead = 1;
			printmsg(ph, DIED);
			pthread_mutex_unlock(&ph->m->mutex);
			break ;
		}
		pthread_mutex_unlock(&ph->m->mutex);
		msleep(2);
	}

	return (NULL);
}

void *act(void *p)
{
	t_phil *ph;
	
	ph = (t_phil *)p;
	ph->time = get_time();
	pthread_create(&ph->monitor, NULL, &monitor, p);
	// pthread_detach(*(ph->thread));
	if ((ph->id + 1) % 2 == 0)
		msleep(ph->m->tteat);
	while (ph->ate)
	{
		eat(ph);
		if (!ph->ate)
			break ;
		printmsg(ph, THINK);
	}

	return (NULL);
}

void create_threads(t_main *m)
{
	int i;
	pthread_t	*threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * m->amount);

	i = 0;
	while (i < m->amount)
	{
		m->id = i;
		pthread_create(&(threads[i]), NULL, act, (void *)(&m->ph[i]));
		// pthread_join(threads[i], NULL);
		m->ph[i].thread = &threads[i];
		i++;
		// usleep(100);
	}
	i = 0;
	while (i < m->amount)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}