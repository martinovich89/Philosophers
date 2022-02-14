/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:58:59 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/14 15:13:48 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	set_mutexed_var(void *var, int val, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*(int *)var = val;
	pthread_mutex_unlock(mutex);
}

void	set_chrono_start(t_vars *vars)
{
	while (vars->philo_count)
	{
		pthread_mutex_lock(&vars->print);
		if (vars->chrono_start)
		{
			pthread_mutex_unlock(&vars->print);
			break ;
		}
		pthread_mutex_unlock(&vars->print);
	}
}

void	wait_all_philo(t_vars *vars)
{
	while (vars->philo_count)
	{
		pthread_mutex_lock(&vars->status_mutex);
		if (vars->phi[vars->philo_count - 1].status == 0)
		{
			pthread_mutex_unlock(&vars->status_mutex);
			break ;
		}
		pthread_mutex_unlock(&vars->status_mutex);
		usleep(100);
	}
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

int	unlock_before_return(pthread_mutex_t *mutex1, pthread_mutex_t *mutex2)
{
	if (mutex1)
		pthread_mutex_unlock(mutex1);
	if (mutex2)
		pthread_mutex_unlock(mutex2);
	return (1);
}
