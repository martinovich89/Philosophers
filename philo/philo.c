/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:20:06 by mhenry            #+#    #+#             */
/*   Updated: 2021/12/19 17:11:23 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_strcpy(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

int	ft_strcat(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (dst[i])
		i++;
	return (ft_strcpy(dst + i, src));
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

void	ft_memset(void *ptr, size_t n, char value)
{
	unsigned char	*recup;
	size_t			i;

	recup = (unsigned char *)ptr;
	i = 0;
	while (i < n)
	{
		recup[i] = value;
		i++;
	}
}

size_t	get_current_time(void)
{
	size_t	time;
	struct	timeval tv;
	struct	timezone tz;

	gettimeofday(&tv, &tz);
	time = tv.tv_sec * 1000000 + tv.tv_usec;
	return (time);
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

void	set_chrono(t_vars *vars)
{
	vars->chrono_start = get_current_time();
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
	vars->is_dead = 0;
	vars->start = 0;
	vars->philo_count = ft_atoi(argv[1]);
	vars->ttd = ft_atoi(argv[2]);
	vars->tte = ft_atoi(argv[3]);
	vars->tts = ft_atoi(argv[4]);
	vars->maxmeal = 0;
	vars->chrono_start = get_current_time();
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
		usleep(200);
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

int	timetostr(char *str, size_t elapsed_time)
{
	int		ret;
	size_t	n;
	size_t	i;

	i = (elapsed_time == 0);
	n = elapsed_time;
	while (str[i])
		i++;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	ret = (int)i;
	if (elapsed_time == 0)
		return (ft_strcat(str, "0"));
	str[i + 1] = '\0';
	while (elapsed_time > 0)
	{
		i--;
		str[i] = elapsed_time % 10 + '0';
		elapsed_time /= 10;
	}
	return (ret);
}

void	build_str_to_print(t_philo *philo)
{
	size_t i;

	i = 0;
	ft_bzero(philo->str_to_print, 100);
	philo->elapsed_time = get_current_time() - philo->vars->chrono_start;
	i += timetostr(philo->str_to_print + i, philo->elapsed_time / 1000);
	i += ft_strcpy(philo->str_to_print + i, " : ");
	i += ft_strcpy(philo->str_to_print + i, philo->status_str);
	i += ft_strcpy(philo->str_to_print + i, " <- ");
	i += timetostr(philo->str_to_print + i, philo->id);
	i += ft_strcpy(philo->str_to_print + i, "\n");
}

int	philo_death_check(t_philo *philo)
{
//	printf("%zu | %zu | %zu\n", philo->id, (get_current_time() - philo->last_meal) / 1000, philo->last_meal);
	if ((get_current_time() - philo->last_meal) / 1000
		> (size_t)philo->vars->ttd)
		return (1);
	return (0);
}

int	update_status(t_philo *philo, int status)
{
	if (philo->vars->chrono_start && philo_death_check(philo))
	{
		write(1, "lul\n", 4);
		pthread_mutex_lock(&philo->vars->death);
		*philo->is_dead = 1;
		pthread_mutex_unlock(&philo->vars->death);
		status = 4;
	}
	if (status == 1)
	{
		philo->status = 1;
		ft_strcpy(philo->status_str, "TIME_TO_EAT");
		philo->last_meal = get_current_time();
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
	else if (status == 4)
	{
		philo->status = 3;
		ft_strcpy(philo->status_str, "TIME_TO_DIE");
		return (1);
	}
	build_str_to_print(philo);
	return (0);
}

int	print_status(t_philo *philo, int status)
{
	char *str;
	
	str = philo->str_to_print;
	(void)status;
	pthread_mutex_lock(&philo->vars->death);
	if (philo->vars->is_dead)
		return (1);
	pthread_mutex_unlock(&philo->vars->death);
	write(1, str, ft_strlen(str));
	return (0);
}

int	sleep_until(t_philo *philo, size_t time_to_stop)
{
	(void)philo;
	while (get_current_time() < time_to_stop)
	{
		pthread_mutex_lock(&philo->vars->death);
		if (philo->vars->is_dead)
			return (1);
		pthread_mutex_unlock(&philo->vars->death);
		usleep(100);
	}
	return (0);
}

int	eat_phase(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->last_fork);
	if (update_status(philo, 1))
		return (1);
	if (print_status(philo, 1))
		return (1);
	if (sleep_until(philo, philo->last_meal + philo->vars->tte * 1000))
		return (1);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->last_fork);
	return (0);
}

int	sleep_phase(t_philo *philo)
{
	if (update_status(philo, 2))
		return (1);
	if (print_status(philo, 2))
		return (1);
	if (sleep_until(philo, philo->last_meal + (philo->vars->tte + philo->vars->tts) * 1000))
		return (1);
	return (0);
}

int	think_phase(t_philo *philo)
{
	if (update_status(philo, 3))
		return (1);
	if (print_status(philo, 3))
		return (1);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	size_t			id;
	pthread_mutex_t	*mutex;
	int				next_id;

	// PHILO VARS INITIALIZATION
	philo = (t_philo *)ptr;
	id = philo->id;
	mutex = philo->vars->mutex;
	next_id = ((int)id != philo->vars->philo_count - 1) * (id + 1);
	philo->left_fork = mutex + id;
	philo->right_fork = mutex + ((int)id != philo->vars->philo_count - 1) * (id + 1);
	fork_attribution(philo);
	pthread_mutex_lock(&philo->vars->print);
	philo->last_meal = philo->vars->chrono_start;
	pthread_mutex_unlock(&philo->vars->print);

/*	int quit = 0;
	while (quit == 0)
	{
		usleep(100);
		pthread_mutex_lock(&philo->vars->print);
		if (philo->vars->start == 1)
			quit = 1;
		pthread_mutex_unlock(&philo->vars->print);
	}
*/
	// EAT PHASE
	while (1)
	{
		if (eat_phase(philo))
			return (ptr);
		if (sleep_phase(philo))
			return (ptr);
		if (think_phase(philo))
			return (ptr);
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

	pthread_mutex_init(&vars->print, NULL);
	pthread_mutex_init(&vars->death, NULL);
	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		if (pthread_mutex_init(&vars->mutex[i], NULL))
			return (-1);
		i++;
	}
	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		vars->philo[i].vars = vars;
		vars->philo[i].id = i;
		vars->philo[i].is_dead = &vars->is_dead;
		if (i % 2 == 0 && pthread_create(&vars->philo[i].thread, NULL, &routine, (void *)(vars->philo + i)) != 0)
			return (-1);
		i++;
	}
	usleep(vars->ttd * 100);
	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		if (i % 2 == 1 && pthread_create(&vars->philo[i].thread, NULL, &routine, (void *)(vars->philo + i)) != 0)
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

void	check_death(t_vars *vars)
{
	while (1)
	{
		pthread_mutex_lock(&vars->death);
		if (vars->is_dead)
			return ;
		pthread_mutex_unlock(&vars->death);
		usleep(100);
	}
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
	check_death(&vars);
	clear_philo_and_mutex(&vars);
	return (0);
}
