#include "header.h"

void act(t_phil *phil)
{
	pthread_mutex_lock(phil->left);
	pthread_mutex_lock(phil->right);
	printf("%d взял вилки \n", phil->id);
	phil->ate++;
	pthread_mutex_unlock(phil->left);
	pthread_mutex_unlock(phil->right);
}

void *init_phil(void *mn)
{
	t_phil	*phil;
	t_main 	*m;

	printf("1111\n");
	m = (t_main *)mn;
	phil =  (t_phil *)malloc(sizeof(t_phil));
	phil->id = m->id;
	phil->ate = 0;
//	printf("текущий id %d-%d\n", m->id, phil->id);
	phil->left = &m->forks[phil->id];
	if (phil->id == m->amount - 1)
		phil->right = &m->forks[0];
	else
		phil->right = &m->forks[phil->id + 1];
//	while (phil->ate < m->eat_num)
//	{
		act (phil);
		pthread_detach(m->thread[phil->id]);
//	}
//	pthread_detach(m->thread[phil->id]);
//	usleep(1000);
//	free(phil);
	return (NULL);
}

void create_philo(t_main *m)
{
	printf("количество:%d время до смерти:%d время поесть:%d время поспать:%d сколько раз поесть:%d\n", m->amount, m->die, m->eat, m->sleep, m->eat_num);
	while (m->id < m->amount)
	{
		printf("id %d amount %d\n", m->id, m->amount);
		pthread_create(&m->thread[m->id], NULL, init_phil, (void*)m);
		usleep(100);
		m->id++;
	}
}