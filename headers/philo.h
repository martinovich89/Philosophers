/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:46:38 by mhenry            #+#    #+#             */
/*   Updated: 2021/11/18 14:21:57 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>

/*
** ttd, tte and tts refer to : time to die, time to eat and time to sleep.
*/

typedef struct	s_vars
{
	pthread_mutex_t	*mutex;
	pthread_t		*philo;
	int				philo_count;
	int				ttd;
	int				tte;
	int				tts;
	int				maxmeal;
}	t_vars;

typedef struct	s_philo
{
	
}	t_philo;

int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(char *str);

#endif
