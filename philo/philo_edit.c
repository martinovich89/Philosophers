/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:41:39 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/14 15:28:17 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

void	build_str_to_print(t_phi *phi, char *str1)
{
	size_t	i;

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
