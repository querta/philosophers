#include "header.h"

int		ft_atoi(char *str)
{
	unsigned long long	num;
	int					i;
	int					sign;

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
		num = (unsigned long long)(num * 10 + str[i] - '0');
		if (num > 9223372036854775807 && sign == 1)
			return (-1);
		if (num > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return ((int)(sign * num));
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	int n;

	n = count * size;
	if ((mem = malloc(n)))
	{
		while (n--)
			*mem++ = '\0';
//		ft_bzero(mem, count * size);
		return (mem);
	}
	return (NULL);
}