#ifndef HEADER_H
# define HEADER_H

# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdint.h>
# include <semaphore.h>
# include <signal.h>

typedef enum e_msg
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED
}					t_msg;

typedef struct s_phil
{
	int				id;
	pid_t			pid;
	pthread_t		*thread;
	pthread_t		monitor;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	uint64_t		time;
	int				ate;
	struct s_main	*m;
}					t_phil;

typedef struct s_main
{
	uint64_t		start_time;
	int				id;
	sem_t			*forks;
	sem_t			*status;
	sem_t			*print;
	int				dead;
	int				amount;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				eat_num;
	int				pstatus;
	t_phil			*ph;
}					t_main;

int					main(int argc, char **argv);
int					ft_atoi(char *str);
void				msleep(uint64_t ms);
uint64_t			timedelta(uint64_t saved_time);
uint64_t			get_time(void);
void				ft_putendl_fd(char *s, int fd);
int					create_threads(t_main *m);

#endif