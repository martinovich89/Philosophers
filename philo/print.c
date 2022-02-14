/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:32:56 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/14 15:48:04 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

int	print_death(t_phi *phi)
{
	build_str_to_print(phi, phi->str_to_print);
	if ((size_t)phi->vars->is_dead == phi->id + 1)
	{
		write(1, phi->str_to_print, ft_strlen(phi->str_to_print));
	}
	phi->vars->stop = 1;
	pthread_mutex_unlock(&phi->vars->death);
	pthread_mutex_unlock(&phi->vars->print);
	return (1);
}

int	print_status(t_phi *phi, pthread_mutex_t *print_mutex,
		pthread_mutex_t *death_mutex)
{
	char	*str;

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
		build_str_to_print(phi, str);
		write(1, str, ft_strlen(str));
	}
	pthread_mutex_unlock(print_mutex);
	return (0);
}
