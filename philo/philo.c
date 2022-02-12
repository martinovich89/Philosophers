/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:20:06 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/12 17:49:56 by mhenry           ###   ########.fr       */
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
	vars->satiated = 0;
	vars->is_dead = 0;
	vars->start = 0;
	vars->stop = 0;
	vars->philo_count = ft_atoi(argv[1]);
	vars->ttd = ft_atoi(argv[2]);
	vars->tte = ft_atoi(argv[3]);
	vars->tts = ft_atoi(argv[4]);
	vars->maxmeal = -1;
	vars->chrono_start = 0;
	if (argc == 6)
		vars->maxmeal = ft_atoi(argv[5]);
	if (vars->philo_count < 0 || vars->ttd < 0 || vars->tte < 0 || vars->tts < 0 || (argc == 6 && vars->maxmeal < 0))
		return (-1);
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

void	fork_attribution(t_phi *phi)
{
	if (phi->id % 2 == 0)
	{
		phi->first_fork = phi->left_fork;
		phi->last_fork = phi->right_fork;
	}
	else
	{
		phi->first_fork = phi->right_fork;
		phi->last_fork = phi->left_fork;
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

void	kek(void)
{
	write(1, "kek\n", 4);
}

void	build_str_to_print(t_phi *phi, char *str1, char *str2)
{
	size_t i;

	(void)str2;
	i = 0;
	ft_bzero(str1, 60);
	phi->elapsed_time = get_current_time() - phi->vars->chrono_start;
	i += timetostr(str1 + i, phi->elapsed_time / 1000);
	i += ft_strcpy(str1 + i, " ");
	i += timetostr(str1 + i, phi->id + 1);
	i += ft_strcpy(str1 + i, " ");
	i += ft_strcpy(str1 + i, phi->status_str);

	i += ft_strcpy(str1 + i, "\n");
}


int	update_status(t_phi *phi, int status)
{
	pthread_mutex_lock(&phi->vars->status_mutex);
	phi->status = status;
	pthread_mutex_unlock(&phi->vars->status_mutex);
	if (status == 0)
		ft_strcpy(phi->status_str, "has taken a fork");
	else if (status == 1)
	{
		ft_strcpy(phi->status_str, "is eating");
		pthread_mutex_lock(&phi->vars->meal);
		phi->last_meal = get_current_time();
		pthread_mutex_unlock(&phi->vars->meal);
	}
	else if (status == 2)
		ft_strcpy(phi->status_str, "is sleeping");
	else if (status == 3)
		ft_strcpy(phi->status_str, "is thinking");
	else if (status == 4)
	{
		pthread_mutex_lock(&phi->vars->death);
		if (phi->vars->is_dead - 1 == (int)phi->id)
			ft_strcpy(phi->status_str, "died");
		pthread_mutex_unlock(&phi->vars->death);
		return (1);
	}
	return (0);
}

int	print_death(t_phi *phi)
{
	build_str_to_print(phi, phi->str_to_print, phi->str_pre_print);
	if ((size_t)phi->vars->is_dead == phi->id + 1)
	{
		write(1, phi->str_to_print, ft_strlen(phi->str_to_print));
	}
	phi->vars->stop = 1;
	pthread_mutex_unlock(&phi->vars->death);
	pthread_mutex_unlock(&phi->vars->print);
	return (1);
}

int	print_status(t_phi *phi, pthread_mutex_t *print_mutex, pthread_mutex_t *death_mutex)
{
	char *str;

	pthread_mutex_lock(print_mutex);
	pthread_mutex_lock(death_mutex);
	if (phi->vars->is_dead)
	{
		ft_strcpy(phi->status_str, "died");
		return (print_death(phi));
	}
	else
	{
		pthread_mutex_unlock(death_mutex);
		str = phi->str_to_print;
		build_str_to_print(phi, str, phi->str_pre_print);
		write(1, str, ft_strlen(str));
	}
	pthread_mutex_unlock(print_mutex);
	return (0);
}

int	unlock_before_return(pthread_mutex_t *mutex1, pthread_mutex_t *mutex2)
{
	if (mutex1)
		pthread_mutex_unlock(mutex1);
	if (mutex2)
		pthread_mutex_unlock(mutex2);
	return (1);
}

int	sleep_until(t_phi *phi, size_t time_to_stop)
{
	(void)phi;
	while (get_current_time() < time_to_stop)
	{
		pthread_mutex_lock(&phi->vars->death);
		if (phi->vars->is_dead)
			return (unlock_before_return(&phi->vars->death, NULL));
		pthread_mutex_unlock(&phi->vars->death);
		usleep(100);
	}
	return (0);
}

int	wait_for_death(t_phi *phi)
{
	pthread_mutex_unlock(phi->first_fork);
	sleep_until(phi, ~0);
	update_status(phi, 4);
	print_status(phi, &phi->vars->print, &phi->vars->death);
	return (1);
}

int	eat_phase(t_phi *phi)
{
	pthread_mutex_lock(phi->first_fork);
	update_status(phi, 0);
	if (print_status(phi, &phi->vars->print, &phi->vars->death))
		return (unlock_before_return(phi->first_fork, NULL));
	if (phi->first_fork == phi->last_fork)
		return (wait_for_death(phi));
	pthread_mutex_lock(phi->last_fork);
	update_status(phi, 0);
	if (print_status(phi, &phi->vars->print, &phi->vars->death))
		return (unlock_before_return(phi->first_fork, phi->last_fork));
	update_status(phi, 1);
	fflush(stdout);
	if (print_status(phi, &phi->vars->print, &phi->vars->death))
		return (unlock_before_return(phi->first_fork, phi->last_fork));
	if (sleep_until(phi, phi->last_meal + phi->vars->tte * 1000))
	{
		unlock_before_return(phi->first_fork, phi->last_fork);
		pthread_mutex_lock(&phi->vars->print);
		pthread_mutex_lock(&phi->vars->death);
		return (print_death(phi));
	}
	pthread_mutex_unlock(phi->first_fork);
	pthread_mutex_unlock(phi->last_fork);
	return (0);
}

int	sleep_phase(t_phi *phi)
{
	update_status(phi, 2);
	if (print_status(phi, &phi->vars->print, &phi->vars->death))
		return (1);
	if (sleep_until(phi, phi->last_meal + (phi->vars->tte + phi->vars->tts) * 1000))
	{
		pthread_mutex_lock(&phi->vars->print);
		pthread_mutex_lock(&phi->vars->death);
		return (print_death(phi));
	}
	return (0);
}

int	think_phase(t_phi *phi)
{
	if (update_status(phi, 3))
		return (1);
	if (print_status(phi, &phi->vars->print, &phi->vars->death))
		return (1);
	return (0);
}

void	*launch_phases(t_phi *phi)
{
	while (1)
	{
		pthread_mutex_lock(&phi->vars->satiated_mutex);
		if (phi->vars->satiated)
		{
			pthread_mutex_unlock(&phi->vars->satiated_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&phi->vars->satiated_mutex);
		if (eat_phase(phi))
			return (NULL);
		phi->meal_count++;
		if (phi->vars->maxmeal != -1 && phi->meal_count >= phi->vars->maxmeal)
		{
			pthread_mutex_lock(&phi->vars->satiated_mutex);
			phi->satiated = 1;
			pthread_mutex_unlock(&phi->vars->satiated_mutex);
		}
		if (sleep_phase(phi))
			return (NULL);
		if (think_phase(phi))
			return (NULL);
	}
}

void	*routine(void *ptr)
{
	t_phi			*phi;
	size_t			id;
	pthread_mutex_t	*mutex;

	phi = (t_phi *)ptr;
	id = phi->id;
	pthread_mutex_lock(&phi->vars->satiated_mutex);
	pthread_mutex_unlock(&phi->vars->satiated_mutex);
	mutex = phi->vars->mutex;
	phi->left_fork = mutex + id;
	phi->right_fork = mutex + ((int)id != phi->philo_count - 1) * (id + 1);
	fork_attribution(phi);
	pthread_mutex_lock(&phi->vars->print);
	pthread_mutex_lock(&phi->vars->status_mutex);
	phi->status = -1;
	pthread_mutex_unlock(&phi->vars->status_mutex);
	if (!phi->vars->chrono_start)
		phi->vars->chrono_start = get_current_time();
	pthread_mutex_lock(&phi->vars->meal);
	phi->last_meal = phi->vars->chrono_start;
	pthread_mutex_unlock(&phi->vars->meal);
	pthread_mutex_unlock(&phi->vars->print);
	return (launch_phases(phi));
}

int	alloc_philo_and_mutex(t_vars *vars)
{
	vars->phi = malloc(sizeof(t_phi) * (vars->philo_count));
	if (!vars->phi)
		return (-1);
	vars->mutex = malloc(sizeof(pthread_mutex_t) * (vars->philo_count));
	if (!vars->mutex)
		return (-1);
	return (0);
}

int init_mutex(t_vars *vars)
{
	size_t i;

	vars->phi->last_meal = 0;
	pthread_mutex_init(&vars->meal, NULL);
	pthread_mutex_init(&vars->satiated_mutex, NULL);
	pthread_mutex_init(&vars->print, NULL);
	pthread_mutex_init(&vars->death, NULL);
	pthread_mutex_init(&vars->status_mutex, NULL);
	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		if (pthread_mutex_init(&vars->mutex[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}

void	init_phi(t_vars *vars)
{
	size_t i;

	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		ft_memset(&vars->phi[i], sizeof(t_phi), 0);
		vars->phi[i].philo_count = vars->philo_count;
		i++;
	}
}

int	init_philo_and_mutex(t_vars *vars)
{
	size_t	i;

	if (init_mutex(vars))
		return (-1);
	init_phi(vars);
	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		vars->phi[i].vars = vars;
		vars->phi[i].id = i;
		if (i % 2 == 0 && pthread_create(&vars->phi[i].philo, NULL, &routine, (void *)(vars->phi + i)) != 0)
			return (-1);
		i++;
	}
	usleep(200);
	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		if (i % 2 == 1 && pthread_create(&vars->phi[i].philo, NULL, &routine, (void *)(vars->phi + i)) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	destroy_all_mutex(t_vars *vars)
{
	size_t i;

	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		pthread_mutex_destroy(vars->mutex + i);
		i++;
	}
	pthread_mutex_destroy(&vars->death);
	pthread_mutex_destroy(&vars->print);
	pthread_mutex_destroy(&vars->meal);
	pthread_mutex_destroy(&vars->satiated_mutex);
	pthread_mutex_destroy(&vars->status_mutex);
}

int clear_philo_and_mutex(t_vars *vars)
{
	size_t	i;

	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		if (vars->phi[i].philo)
			pthread_join(vars->phi[i].philo, NULL);
		i++;
	}
	destroy_all_mutex(vars);
	free(vars->phi);
	vars->phi = NULL;
	free(vars->mutex);
	vars->mutex = NULL;
	return (0);
}

int	check_death(t_vars *vars)
{
	pthread_mutex_lock(&vars->death);
	if (vars->is_dead)
		return (unlock_before_return(&vars->death, NULL));
	pthread_mutex_unlock(&vars->death);
	return (0);
}

int	philo_death_check(t_phi *phi)
{
	if ((get_current_time() - phi->last_meal) / 1000
		> (size_t)phi->vars->ttd)
		return (1);
	return (0);
}

void	set_mutexed_var(void *var, int val, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*(int *)var = val;
	pthread_mutex_unlock(mutex);
}

void	check_philo_status(t_vars *vars)
{
	size_t it[2];

	while (1)
	{
		it[0] = 0;
		it[1] = 0;
		while (it[0] < (size_t)vars->philo_count)
		{
			pthread_mutex_lock(&vars->meal);
			if (vars->phi[it[0]].last_meal && philo_death_check(vars->phi + it[0]))
			{
				pthread_mutex_unlock(&vars->meal);
				set_mutexed_var(&vars->is_dead, it[0] + 1, &vars->death);
				return ;
			}
			pthread_mutex_unlock(&vars->meal);
			pthread_mutex_lock(&vars->satiated_mutex);
			if (vars->phi[it[0]].satiated)
				it[1]++;
			pthread_mutex_unlock(&vars->satiated_mutex);
			it[0]++;
		}
		if (it[1] >= (size_t)vars->philo_count)
			return set_mutexed_var(&vars->satiated, 1, &vars->satiated_mutex);
	}
}

void set_chrono_start(t_vars *vars)
{
	while (vars->philo_count)
	{
		pthread_mutex_lock(&vars->print);
		if (vars->chrono_start)
		{
			pthread_mutex_unlock(&vars->print);
			break;
		}
		pthread_mutex_unlock(&vars->print);
	}
}

void wait_all_philo(t_vars *vars)
{
	while (vars->philo_count)
	{
		pthread_mutex_lock(&vars->status_mutex);
		if (vars->phi[vars->philo_count - 1].status == 0)
		{
			pthread_mutex_unlock(&vars->status_mutex);
			break;
		}
		pthread_mutex_unlock(&vars->status_mutex);
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
	alloc_philo_and_mutex(&vars);
	init_philo_and_mutex(&vars);
	set_chrono_start(&vars);
	wait_all_philo(&vars);
	check_philo_status(&vars);
	clear_philo_and_mutex(&vars);
	return (0);
}
