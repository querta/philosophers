#ifndef HEADER_H
# define HEADER_H

# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef pthread_mutex_t mut_t;
typedef struct 	timeval t_time;

typedef struct 		s_phil
{
	int				id;
//	int				dead;
	pthread_t		*thread;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	uint64_t 		time;
	int				ate;
}					t_phil;


typedef struct		s_main
{
	uint64_t 		start_time;
	pthread_t		*thread;
	int				id;
	pthread_mutex_t	*forks;
	int				dead;
	int				amount;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				eat_num;
	t_phil			*ph;
}					t_main;

int					main(int argc, char **argv);
int					ft_atoi(char *str);
// void				create_philo(t_main *m);
void				msleep(uint64_t ms);
void create_threads(t_main *m);
uint64_t			get_time(void);
uint64_t			timedelta(uint64_t saved_time);


#endif