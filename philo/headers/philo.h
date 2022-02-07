/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:46:38 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/07 14:38:21 by mhenry           ###   ########.fr       */
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

typedef struct	s_phi
{
	struct s_vars	*vars;
	pthread_t		philo;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t *last_fork;
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
}	t_phi;

typedef struct	s_vars
{
	int				satiated;
	int				is_dead;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	death;
	pthread_mutex_t print;
	pthread_mutex_t meal;
	pthread_mutex_t satiated_mutex;
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

void	set_mutexed_var(void *var, int val, pthread_mutex_t *mutex);

#endif
