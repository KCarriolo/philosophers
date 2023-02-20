
#include "philo.h"

int	fail_validation(char **str, int args)
{
	int	i;
	int	j;

	i = 1;
	if (!(args == 4 || args == 5))
		return (1);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] && str[i][j] >= '0' && str[i][j] <= '9')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (intmax_validation(str));
}

int	intmax_validation(char **str)
{
	int		i;
	long	n;

	i = 1;
	while (str[i])
	{
		n = ph_atol(str[i]);
		if (n == 0)
			return (1);
		if (n > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

long int	ph_atol(char *str)
{
	int		i;
	long	ret;	

	i = 0;
	ret = 0;
	while (str[i])
		ret = ret * 10 + (str[i++] - 48);
	return (ret);
}
