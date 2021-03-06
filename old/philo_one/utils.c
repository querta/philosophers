#include "header.h"

int	ft_atoi(char *str)
{
	uint64_t	num;
	int			i;
	int			sign;

	num = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (uint64_t)(num * 10 + str[i] - '0');
		if (num > 9223372036854775807 && sign == 1)
			return (-1);
		if (num > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return ((int)(sign * num));
}

uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		time;

	time = -1;
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

uint64_t	timedelta(uint64_t saved_time)
{
	uint64_t	time;

	time = get_time() - saved_time;
	return (time);
}

void	msleep(uint64_t ms)
{
	uint64_t	i;

	i = get_time();
	while (get_time() - i < ms)
		usleep(500);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
			write(fd, (s++), 1);
	}
	write(fd, "\n", 1);
}
