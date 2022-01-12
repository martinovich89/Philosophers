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
	vars->chrono_start = 0;
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

/*void	build_str_pre_print(t_phi *phi, char *str)
{
	size_t i;

	i = 0;
	ft_bzero(str, 40);
	i += timetostr(str + i, phi->id + 1);
	i += ft_strcpy(str + i, " ");
	i += ft_strcpy(str + i, phi->status_str);
}

void	build_str_to_print(t_phi *phi, char *str1, char *str2)
{
	size_t i;

	i = 0;
	ft_bzero(str1, 60);
	phi->elapsed_time = get_current_time() - phi->vars->chrono_start;
	i += timetostr(str1 + i, phi->elapsed_time / 1000);
	i += ft_strcpy(str1 + i, " ");
	i += ft_strcpy(str1 + i, str2);
	i += ft_strcpy(str1 + i, "\n");
}*/

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
/*	if (phi->vars->chrono_start)
	{
		pthread_mutex_lock(&phi->vars->death);
		if (phi->vars->is_dead)
			status = 4;
		pthread_mutex_unlock(&phi->vars->death);
	}*/
	if (status == 0)
	{
		phi->status = 0;
		ft_strcpy(phi->status_str, "has taken a fork");
	}
	else if (status == 1)
	{
		phi->status = 1;
		ft_strcpy(phi->status_str, "is eating");
		phi->last_meal = get_current_time();
	}
	else if (status == 2)
	{
		phi->status = 2;
		ft_strcpy(phi->status_str, "is sleeping");
	}
	else if (status == 3)
	{
		phi->status = 3;
		ft_strcpy(phi->status_str, "is thinking");
	}
	else if (status == 4)
	{
		if (phi->vars->is_dead - 1 == (int)phi->id)
		{
			phi->status = 4;
			ft_strcpy(phi->status_str, "has died");
		}
		return (1);
	}
	return (0);
}

int	print_death(t_phi *phi)
{
	write(1, "kek1\n", 5);
	build_str_to_print(phi, phi->str_to_print, phi->str_pre_print);
	if (phi->status == 4)
		write(1, phi->str_to_print, ft_strlen(phi->str_to_print));
	pthread_mutex_unlock(&phi->vars->death);
	pthread_mutex_unlock(&phi->vars->print);
	return (1);
}

int	print_status(t_phi *phi, pthread_mutex_t *print_mutex, pthread_mutex_t *death_mutex)
{
	char *str;

	pthread_mutex_lock(print_mutex);
//	build_str_pre_print(phi, phi->str_pre_print);
	pthread_mutex_lock(death_mutex);
	if (phi->vars->is_dead)
	{
		update_status(phi, 4);
//		build_str_pre_print(phi, phi->str_pre_print);
//		pthread_mutex_lock(print_mutex);	
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

int	eat_phase(t_phi *phi)
{
	pthread_mutex_lock(phi->first_fork);
	update_status(phi, 0);
	if (print_status(phi, &phi->vars->print, &phi->vars->death))
		return (unlock_before_return(phi->first_fork, NULL));
	pthread_mutex_lock(phi->last_fork);
	update_status(phi, 0);
	if (print_status(phi, &phi->vars->print, &phi->vars->death))
		return (unlock_before_return(phi->first_fork, phi->last_fork));
	update_status(phi, 1);
	if (print_status(phi, &phi->vars->print, &phi->vars->death))
		return (unlock_before_return(phi->first_fork, phi->last_fork));
	if (sleep_until(phi, phi->last_meal + phi->vars->tte * 1000))
	{
		unlock_before_return(phi->first_fork, phi->last_fork);
		pthread_mutex_lock(&phi->vars->print);
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

void	*routine(void *ptr)
{
	t_phi			*phi;
	size_t			id;
	pthread_mutex_t	*mutex;
	int				next_id;

	// phi VARS INITIALIZATION
	phi = (t_phi *)ptr;
	id = phi->id;
	phi->satiated = 0;
	mutex = phi->vars->mutex;
	next_id = ((int)id != phi->vars->philo_count - 1) * (id + 1);
	phi->left_fork = mutex + id;
	phi->right_fork = mutex + ((int)id != phi->vars->philo_count - 1) * (id + 1);
	fork_attribution(phi);
	pthread_mutex_lock(&phi->vars->print);
	printf("%zu\r", phi->vars->chrono_start);
//	fflush(stdout);
	if (!phi->vars->chrono_start)
	{
		phi->vars->chrono_start = get_current_time();
	}
	phi->last_meal = phi->vars->chrono_start;
	pthread_mutex_unlock(&phi->vars->print);

/*	int quit = 0;
	while (quit == 0)
	{
		usleep(100);
		pthread_mutex_lock(&phi->vars->print);
		if (phi->vars->start == 1)
			quit = 1;
		pthread_mutex_unlock(&phi->vars->print);
	}
*/
	// EAT PHASE
	while (1)
	{
		if (eat_phase(phi))
		{
			return (NULL);
		}
		if (sleep_phase(phi))
		{
			return (NULL);
		}
		if (think_phase(phi))
		{
			return (NULL);
		}
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
	vars->phi = malloc(sizeof(t_phi) * (vars->philo_count));
	if (!vars->phi)
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
//	printf("%zu | %zu | %zu\n", phi->id, (get_current_time() - phi->last_meal) / 1000, phi->last_meal);
//	printf("%zu | %zu\n", (get_current_time() - phi->last_meal) / 1000, (size_t)phi->vars->ttd);
	if ((get_current_time() - phi->last_meal) / 1000
		> (size_t)phi->vars->ttd)
		return (1);
	return (0);
}

void	check_philo_status(t_vars *vars)
{
	size_t	i;
	size_t	n;

	while (1)
	{
		i = 0;
		n = 0;
		while (i < (size_t)vars->philo_count)
		{
			//printf("%zu\n", vars->phi[i].last_meal);
			if (vars->phi[i].last_meal && philo_death_check(vars->phi + i))
			{
				pthread_mutex_lock(&vars->death);
				vars->is_dead = i + 1;
				printf("%zu, %zu, %zu\n", i, vars->phi[i].last_meal, get_current_time() - vars->phi[i].last_meal);
				pthread_mutex_unlock(&vars->death);
				kek();
				return ;
			}
			if (vars->phi[i].satiated)
				n++;
			i++;
		}
		if (n == (size_t)vars->philo_count)
			return ;
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
	**	INIT phiS
	*/
	alloc_philo_and_mutex(&vars);
	/*
	**	LAUNCH THREADS
	*/
	init_philo_and_mutex(&vars);
	/*
	**	CHECK END CONDITION
	**		while (!(phi_dead() || curmeal == maxmeal))
	**	JOIN THREADS
	*/
	/*
	**	CLEAR
	*/
	while (1)
	{
		pthread_mutex_lock(&vars.print);
		if (vars.chrono_start)
		{
			unlock_before_return(&vars.print, NULL);
			break;
		}
		pthread_mutex_unlock(&vars.print);
	}
	check_philo_status(&vars);
	clear_philo_and_mutex(&vars);
	return (0);
}
