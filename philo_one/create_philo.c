#include "header.h"

void act(t_main *m, t_phil *phil)
{
	while (1)
	{
		pthread_mutex_lock(phil->left);
		printf("%lldms ", timedelta(m->start_time));
		printf("%d has taken a fork %p\n", phil->id, phil->right);
		pthread_mutex_lock(phil->right);
		printf("%lldms ", timedelta(m->start_time));
		printf("%d has taken a fork %p\n", phil->id, phil->left);
		printf("%lldms ", timedelta(m->start_time));
		printf("%d is eating \n", phil->id);
		usleep (m->tteat * 1000);
//usleep (10000);
		phil->time = get_time();
		phil->ate++;
		pthread_mutex_unlock(phil->left);
		pthread_mutex_unlock(phil->right);
		if (phil->ate == m->eat_num)
			break ;
		printf("%lldms ", timedelta(m->start_time));
		printf("%d is sleeping \n", phil->id);
		usleep(m->ttsleep * 1000);
		printf("%lldms ", timedelta(m->start_time));
		printf("%d is thinking \n", phil->id);
	}
}

//void	*philo(void *array)
//{
//	t_philo	*philo;
//
//	philo = (t_philo*)array;
//	while (LOOP)
//	{
//		pthread_mutex_lock(philo->left_fork);
//		print_state(" has taken a fork\n", philo->philo_id);
//		pthread_mutex_lock(philo->right_fork);
//		print_state(" has taken a fork\n", philo->philo_id);
//		pthread_mutex_lock(&(philo->check_death_mutex));
//		g_death_trigger[philo->philo_id] = ON;
//		pthread_mutex_unlock(&(philo->check_death_mutex));
//		print_state(" is eating\n", philo->philo_id);
//		msleep(philo->time_to_eat);
//		pthread_mutex_unlock(philo->left_fork);
//		pthread_mutex_unlock(philo->right_fork);
//		philo->num_of_times_eat -= 1;
//		if (philo->argc == 6 && philo->num_of_times_eat == 0)
//			break ;
//		print_state(" is sleeping\n", philo->philo_id);
//		msleep(philo->time_to_sleep);
//		print_state(" is thinking\n", philo->philo_id);
//	}
//	g_death_trigger[philo->philo_id] = FOOL;
//	return (NULL);
//}

void *init_phil(void *mn)
{
	t_phil	*phil;
	t_main 	*m;

	m = (t_main *)mn;
	phil = (t_phil *)malloc(sizeof(t_phil));
	phil->id = m->id;
//	pthread_detach(m->thread[m->id]);
	printf("филосов %d:\n", phil->id);
	usleep(1000000 * 10);
	phil->ate = 0;
	phil->left = &m->forks[phil->id];
	if (phil->id == m->amount - 1)
		phil->right = &m->forks[0];
	else
		phil->right = &m->forks[phil->id + 1];
//		act (m, phil);
	usleep(10000);

	return (NULL);
}

void create_philo(t_main *m)
{
	m->thread = (pthread_t *)malloc(m->amount * sizeof(pthread_t));
	while (m->id < m->amount)
	{
		pthread_create(&(m->thread[m->id]), NULL, init_phil, (void *)m);
		usleep(100);
		m->id++;
	}
}
//
//int		threads_init(t_philo **philos)
//{
//	int			i;
//	pthread_t	*threads;
//
//	i = 0;
//	if (!(threads = (pthread_t *)malloc(sizeof(pthread_t) *
//										g_philo_count)))
//		return (1);
//	g_ptt = threads;
//	while (i < g_philo_count)
//	{
//		if (pthread_create(&(threads[i]), NULL, philo,
//						   (void *)&((*philos)[i])))
//			return (1);
//		(*philos)[i].thread = &(threads[i]);
//		i++;
//		usleep(100);
//	}
//	return (0);
//}
