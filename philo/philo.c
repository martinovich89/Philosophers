/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:20:06 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/14 15:09:16 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/philo.h"

void	*routine(void *ptr)
{
	t_phi			*phi;
	size_t			id;
	pthread_mutex_t	*mutex;

	phi = (t_phi *)ptr;
	id = phi->id;
	pthread_mutex_lock(&phi->vars->satiated_mutex);
	pthread_mutex_unlock(&phi->vars->satiated_mutex);
	mutex = phi->vars->mutex;
	phi->left_fork = mutex + id;
	phi->right_fork = mutex + ((int)id != phi->philo_count - 1) * (id + 1);
	fork_attribution(phi);
	pthread_mutex_lock(&phi->vars->print);
	pthread_mutex_lock(&phi->vars->status_mutex);
	phi->status = -1;
	pthread_mutex_unlock(&phi->vars->status_mutex);
	if (!phi->vars->chrono_start)
		phi->vars->chrono_start = get_current_time();
	pthread_mutex_lock(&phi->vars->meal);
	phi->last_meal = phi->vars->chrono_start;
	pthread_mutex_unlock(&phi->vars->meal);
	pthread_mutex_unlock(&phi->vars->print);
	return (launch_phases(phi));
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc < 5 || argc > 6)
		return (1);
	if (set_vars(argc, argv, &vars))
		return (2);
	alloc_philo_and_mutex(&vars);
	init_philo_and_mutex(&vars);
	set_chrono_start(&vars);
	wait_all_philo(&vars);
	check_philo_status(&vars);
	clear_philo_and_mutex(&vars);
	return (0);
}
