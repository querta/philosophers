#ifndef HEADER_H
# define HEADER_H

# include <string.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_main
{
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	int				dead;
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				eat_num;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

}				t_main;

#endif