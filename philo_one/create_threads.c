#include "header.h"

void act(void *mn)
{
	t_main *m;
	t_phil *ph;

	m = (t_main *)mn;
	ph = &(m->ph[m->id]);

}

void create_threads(t_main *m)
{
	int i;

	i = 0;
	while (i < m->amount)
	{
		m->id = i;
		// pthread_create(&(m->ph[i].thread), NULL, &act, (void *)m);
		i++;
	}
}