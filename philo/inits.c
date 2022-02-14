/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:31:00 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/14 15:30:43 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

int	set_vars(int argc, char **argv, t_vars *vars)
{
	size_t	i;

	i = 1;
	while ((int)i < argc - 1)
	{
		if (check_arg(argv[i]))
			return (-1);
		i++;
	}
	vars->satiated = 0;
	vars->is_dead = 0;
	vars->start = 0;
	vars->stop = 0;
	vars->philo_count = ft_atoi(argv[1]);
	vars->ttd = ft_atoi(argv[2]);
	vars->tte = ft_atoi(argv[3]);
	vars->tts = ft_atoi(argv[4]);
	vars->maxmeal = -1;
	vars->chrono_start = 0;
	if (argc == 6)
		vars->maxmeal = ft_atoi(argv[5]);
	if (vars->philo_count < 0 || vars->ttd < 0
		|| vars->tte < 0 || vars->tts < 0 || (argc == 6 && vars->maxmeal < 0))
		return (-1);
	return (0);
}

void	fork_attribution(t_phi *phi)
{
	if (phi->id % 2 == 0)
	{
		phi->first_fork = phi->left_fork;
		phi->last_fork = phi->right_fork;
	}
	else
	{
		phi->first_fork = phi->right_fork;
		phi->last_fork = phi->left_fork;
	}
}

int	init_mutex(t_vars *vars)
{
	size_t	i;

	vars->phi->last_meal = 0;
	pthread_mutex_init(&vars->meal, NULL);
	pthread_mutex_init(&vars->satiated_mutex, NULL);
	pthread_mutex_init(&vars->print, NULL);
	pthread_mutex_init(&vars->death, NULL);
	pthread_mutex_init(&vars->status_mutex, NULL);
	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		if (pthread_mutex_init(&vars->mutex[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}

void	init_phi(t_vars *vars)
{
	size_t	i;

	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		ft_memset(&vars->phi[i], sizeof(t_phi), 0);
		vars->phi[i].philo_count = vars->philo_count;
		i++;
	}
}

int	init_philo_and_mutex(t_vars *vars)
{
	size_t	i;

	if (init_mutex(vars))
		return (-1);
	init_phi(vars);
	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		vars->phi[i].vars = vars;
		vars->phi[i].id = i;
		if (i % 2 == 0 && pthread_create(&vars->phi[i].philo,
				NULL, &routine, (void *)(vars->phi + i)) != 0)
			return (-1);
		i++;
	}
	usleep(200);
	i = 0;
	while (i < (size_t)vars->philo_count)
	{
		if (i % 2 == 1 && pthread_create(&vars->phi[i].philo,
				NULL, &routine, (void *)(vars->phi + i)) != 0)
			return (-1);
		i++;
	}
	return (0);
}
