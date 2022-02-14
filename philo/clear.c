/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:02:34 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/14 15:12:49 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

void	destroy_all_mutex(t_vars *vars)
{
	size_t	i;

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

int	clear_philo_and_mutex(t_vars *vars)
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
