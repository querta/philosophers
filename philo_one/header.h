#ifndef HEADER_H
# define HEADER_H

# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef pthread_mutex_t mut_t;

typedef struct s_phil
{
	int				id;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	int				ate;
}				t_phil;

typedef struct s_main
{
	pthread_t		*thread;
	int				id;
	pthread_mutex_t	*forks;
	int				dead;
	int				amount;
	int				die;
	int				eat;
	int				sleep;
	int				eat_num;
}				t_main;

int		main(int argc, char **argv);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(char *str);
void	create_philo(t_main *m);

#endif