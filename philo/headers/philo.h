/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:46:38 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/14 15:11:15 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>

/*
** ttd, tte and tts refer to : time to die, time to eat and time to sleep.
*/

typedef struct s_phi
{
	struct s_vars	*vars;
	pthread_t		philo;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*last_fork;
	int				is_dead;
	int				meal_count;
	int				satiated;
	size_t			id;
	int				status;
	char			status_str[20];
	char			str_pre_print[40];
	char			str_to_print[60];
	size_t			last_meal;
	size_t			elapsed_time;
	int				philo_count;
}	t_phi;

typedef struct s_vars
{
	int				satiated;
	int				is_dead;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	pthread_mutex_t	satiated_mutex;
	pthread_mutex_t	status_mutex;
	t_phi			*phi;
	int				philo_count;
	int				ttd;
	int				tte;
	int				tts;
	int				maxmeal;
	size_t			chrono_start;
	int				start;
	int				stop;
}	t_vars;

int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(char *str);
int		is_digit(char c);
int		ft_strcpy(char *dst, char *src);
int		ft_strcat(char *dst, char *src);
void	ft_bzero(char *str, size_t n);
void	ft_memset(void *ptr, size_t n, char value);
size_t	get_current_time(void);
int		invalid_nbs(char **argv);
int		check_arg(char *str);
void	set_chrono(t_vars *vars);
int		set_vars(int argc, char **argv, t_vars *vars);
int		my_usleep(size_t time, struct timeval *tv, struct timezone *tz);
void	fork_attribution(t_phi *phi);
int		timetostr(char *str, size_t elapsed_time);
void	build_str_to_print(t_phi *phi, char *str1);
int		update_status(t_phi *phi, int status);
int		print_death(t_phi *phi);
int		print_status(t_phi *phi, pthread_mutex_t *print_mutex,
			pthread_mutex_t *death_mutex);
int		unlock_before_return(pthread_mutex_t *mutex1, pthread_mutex_t *mutex2);
int		sleep_until(t_phi *phi, size_t time_to_stop);
int		wait_for_death(t_phi *phi);
int		eat_phase(t_phi *phi);
int		sleep_phase(t_phi *phi);
int		think_phase(t_phi *phi);
void	*launch_phases(t_phi *phi);
int		alloc_philo_and_mutex(t_vars *vars);
int		init_mutex(t_vars *vars);
void	init_phi(t_vars *vars);
int		init_philo_and_mutex(t_vars *vars);
void	destroy_all_mutex(t_vars *vars);
int		clear_philo_and_mutex(t_vars *vars);
int		check_death(t_vars *vars);
int		philo_death_check(t_phi *phi);
void	set_mutexed_var(void *var, int val, pthread_mutex_t *mutex);
void	check_philo_status(t_vars *vars);
void	set_chrono_start(t_vars *vars);
void	wait_all_philo(t_vars *vars);
void	*routine(void *ptr);

void	set_mutexed_var(void *var, int val, pthread_mutex_t *mutex);

#endif
