/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:20:06 by mhenry            #+#    #+#             */
/*   Updated: 2021/11/25 17:18:03 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

void	ft_strcpy(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

void	ft_strcat(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (dst[i])
		i++;
	ft_strcpy(dst + i, src);
}

void	ft_bzero(char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
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
	struct timeval	tv;
	struct timezone	tz;
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
	gettimeofday(&tv, &tz);
	vars->chrono_start = tv.tv_sec * 1000000 + tv.tv_usec;
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

void	fork_attribution(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = philo->left_fork;
		philo->last_fork = philo->right_fork;
	}
	else
	{
		philo->first_fork = philo->right_fork;
		philo->last_fork = philo->left_fork;
	}
}

void	timetostr(char *str, size_t cur_time)
{
	size_t	n;
	size_t	i;

	i = (cur_time == 0);
	n = cur_time;
	while (str[i])
		i++;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	if (cur_time == 0)
		return (ft_strcat(str, "0"));
	str[i + 1] = '\0';
	while (cur_time > 0)
	{
		i--;
		str[i] = cur_time % 10 + '0';
		cur_time /= 10;
	}
}

void	build_str_to_print(t_philo *philo)
{
	ft_bzero(philo->str_to_print, 100);
	gettimeofday(&philo->tv, &philo->tz);
	philo->cur_time = philo->tv.tv_sec * 1000000 + philo->tv.tv_usec - philo->vars->chrono_start;;
	timetostr(philo->str_to_print, philo->cur_time / 1000);
	ft_strcat(philo->str_to_print, " : ");
	ft_strcat(philo->str_to_print, philo->status_str);
	ft_strcat(philo->str_to_print, " <- ");
	timetostr(philo->str_to_print, philo->id);
	ft_strcat(philo->str_to_print, "\n");;
}

void	update_status(t_philo *philo, int status)
{
	if (status == 1)
	{
		philo->status = 1;
		ft_strcpy(philo->status_str, "TIME_TO_EAT");
	}
	else if (status == 2)
	{
		philo->status = 2;
		ft_strcpy(philo->status_str, "TIME_TO_SLEEP");
	}
	else if (status == 3)
	{
		philo->status = 3;
		ft_strcpy(philo->status_str, "TIME_TO_THINK");
	}
	build_str_to_print(philo);
}

void	print_status(t_philo *philo, int status)
{
	char *str;
	
	str = philo->str_to_print;
	(void)status;
	write(1, str, ft_strlen(str));
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	size_t			id;
	pthread_mutex_t	*mutex;


	// PHILO VARS INITIALIZATION
	philo = (t_philo *)ptr;
	id = philo->id;
	mutex = philo->vars->mutex;
	philo->left_fork = mutex + id;
	philo->right_fork = mutex + ((int)id != philo->vars->philo_count - 1) * (id + 1);
	fork_attribution(philo);

	// EAT PHASE
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->last_fork);
	update_status(philo, 1);
	print_status(philo, 1);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->last_fork);

	usleep(1000000);

	// SLEEP PHASE
	update_status(philo, 2);
	print_status(philo, 2);
	
	// THINK PHASE

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
	vars->philo = malloc(sizeof(t_philo) * (vars->philo_count));
	if (!vars->philo)
		return (-1);
	vars->mutex = malloc(sizeof(pthread_mutex_t) * (vars->philo_count));
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
		vars->philo[i].vars = vars;
		vars->philo[i].id = i;
		vars->philo[i].is_dead = &vars->is_dead;
		if (pthread_mutex_init(&vars->mutex[i], NULL))
			return (-1);
		if (pthread_create(&vars->philo[i].thread, NULL, &routine, (void *)(vars->philo + i)) != 0)
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
		if (vars->philo[i].thread)
			pthread_join(vars->philo[i].thread, NULL);
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
