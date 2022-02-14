/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:55:35 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/14 15:23:56 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

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
		ft_strcpy(phi->status_str, "died");
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
	if (sleep_until(phi, phi->last_meal
			+ (phi->vars->tte + phi->vars->tts) * 1000))
	{
		pthread_mutex_lock(&phi->vars->print);
		pthread_mutex_lock(&phi->vars->death);
		ft_strcpy(phi->status_str, "died");
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
