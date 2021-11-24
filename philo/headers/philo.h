/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:46:38 by mhenry            #+#    #+#             */
/*   Updated: 2021/11/24 18:16:25 by mhenry           ###   ########.fr       */
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

typedef struct	s_philo
{
	struct s_vars	*vars;
	pthread_t		thread;
	pthread_mutex_t	fork;
	size_t			id;
	int				is_dead;

}	t_philo;

typedef struct	s_vars
{
	pthread_mutex_t	*mutex;
	t_philo			*philo;
	int				philo_count;
	int				ttd;
	int				tte;
	int				tts;
	int				maxmeal;
	int				someone_dead;
}	t_vars;

int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(char *str);

#endif
