/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:20:06 by mhenry            #+#    #+#             */
/*   Updated: 2021/11/23 17:19:11 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	invalid_nbs(char **argv)
{
	if (ft_strlen(argv[1]) > 12 || ft_strlen(argv[2]) > 12
		|| ft_strlen(argv[3]) > 12 || ft_strlen(argv[4]) > 12)
			return (1);
	return (0);
}

int	check_arg(char *str)
{
	size_t	i;

	i = 0;
	while (is_digit(str[i]))
		i++;
	return (str[i] != '\0');
}

int	set_vars(int argc, char **argv, t_vars *vars)
{
	size_t i;

	i = 1;
	while ((int)i < argc - 1)
	{
		if (check_arg(argv[i]))
			return (-1);
		i++;
	}
	vars->philo_count = ft_atoi(argv[1]);
	vars->ttd = ft_atoi(argv[2]);
	vars->tte = ft_atoi(argv[3]);
	vars->tts = ft_atoi(argv[4]);
	if (argc == 6)
		vars->maxmeal = ft_atoi(argv[5]);
	return (0);
}

int	my_usleep(size_t time, struct timeval *tv, struct timezone *tz)
{
	double	oldtime;
	double	newtime;
	double	time_f;

	gettimeofday(tv, tz);
	time_f = (double)time / 1000000;
	oldtime = (double)tv->tv_sec + (double)tv->tv_usec / 1000000;
	newtime = oldtime;
	while (newtime - oldtime < time_f)
	{
		usleep(100);
		if (!gettimeofday(tv, tz))
			return (-1);
		newtime = (double)tv->tv_sec + (double)tv->tv_usec / 1000000;
	}
	return (0);
}

void	*routine(void *ptr)
{
	struct	timeval tv;
	struct	timezone tz;
	size_t id;

	(void)tv;
	(void)tz;
	id = (size_t)ptr + 1;
	fflush(stdout);
	if (id % 2 == 1)
	{
//		printf("%zu\n", id);
		write(1, "kek\n", 4);
	}
	if (id % 2 == 0)
	{
//		my_usleep(10000, &tv, &tz);
		usleep(60000);
//		printf("%zu\n", id);
		write(1, "lel\n", 4);
	}
	/*
	**	PHASE MANGER :
	**		print manger
	**		manger
	**		lacher fourchettes
	**	PHASE DORMIR :
	**		print dormir
	**		dormir
	**	PHASE PENSER :
	**		print penser
	**		demander fourchette
	*/
	return (NULL);
}

int	alloc_philo_and_mutex(t_vars *vars)
{
	vars->philo = malloc(sizeof(pthread_t) * (vars->philo_count + 1));
	if (!vars->philo)
		return (-1);
	vars->mutex = malloc(sizeof(pthread_mutex_t) * (vars->philo_count + 1));
	if (!vars->mutex)
		return (-1);
	return (0);
}

int	init_philo_and_mutex(t_vars *vars)
{
	size_t	i;

	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		if (pthread_mutex_init(vars->mutex + i, NULL))
			return (-1);
		if (pthread_create(vars->philo + i, NULL, &routine, (void *)i) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int clear_philo_and_mutex(t_vars *vars)
{
	size_t	i;

	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		if (vars->philo[i])
			pthread_join(vars->philo[i], NULL);
		i++;
	}
	free(vars->philo);
	vars->philo = NULL;
	free(vars->mutex);
	vars->mutex = NULL;
	return (0);
}

int main(int argc, char **argv)
{
	t_vars vars;

	if (argc < 5 || argc > 6)
		return (1);
	if (set_vars(argc, argv, &vars))
		return (2);
	printf("%d | %d | %d | %d\n", vars.philo_count, vars.ttd, vars.tte, vars.tts);
	/*
	**	INIT PHILOS
	*/
	alloc_philo_and_mutex(&vars);
	/*
	**	LAUNCH THREADS
	*/
	init_philo_and_mutex(&vars);
	/*
	**	CHECK END CONDITION
	**		while (!(philo_dead() || curmeal == maxmeal))
	**	JOIN THREADS
	*/
	/*
	**	CLEAR
	*/
	clear_philo_and_mutex(&vars);
	return (0);
}
