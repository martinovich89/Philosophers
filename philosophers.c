#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "./headers/philo.h" 

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s2[i] - s1[i]);
}

int		ft_atoi(char *str)
{
	size_t	i;
	int		sign;
	int		nb;

	if (ft_strcmp(str, "-2147483648") == 0)
		return (-2147483648);
	nb = 0;
	sign = (str[0] != '-') * 2 - 1;
	i = (str[0] == '-');
	while (str[i])
	{
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	return (nb * sign);
}

void	set_vars(char **argv, t_vars *vars)
{
	vars->philos = ft_atoi(argv[1]);
	vars->ttd = ft_atoi(argv[2]);
	vars->tte = ft_atoi(argv[3]);
	vars->tts = ft_atoi(argv[4]);
}

int main(int argc, char **argv)
{
	t_vars vars;

	if (argc != 5)
		return (1);
	set_vars(argv, &vars);
	printf("%d | %d | %d | %d\n", vars.philos, vars.ttd, vars.tte, vars.tts);
}
