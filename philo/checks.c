/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:28:02 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/14 15:42:19 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

int	invalid_nbs(char **argv)
{
	if (ft_strlen(argv[1]) > 12 || ft_strlen(argv[2]) > 12
		|| ft_strlen(argv[3]) > 12 || ft_strlen(argv[4]) > 12)
		return (1);
	return (0);
}

int	check_arg(char *str)
{
	size_t	i;

	i = 0;
	while (is_digit(str[i]))
		i++;
	return (str[i] != '\0');
}

int	check_death(t_vars *vars)
{
	pthread_mutex_lock(&vars->death);
	if (vars->is_dead)
		return (unlock_before_return(&vars->death, NULL));
	pthread_mutex_unlock(&vars->death);
	return (0);
}

int	philo_death_check(t_phi *phi)
{
	if ((get_current_time() - phi->last_meal) / 1000
		> (size_t)phi->vars->ttd)
		return (1);
	return (0);
}

void	check_philo_status(t_vars *vars)
{
	unsigned int	it[2];

	while (1)
	{
		*(u_int64_t *)it = 0;
		while (it[0] < (size_t)vars->philo_count)
		{
			pthread_mutex_lock(&vars->meal);
			if (vars->phi[it[0]].last_meal
				&& philo_death_check(vars->phi + it[0]))
			{
				pthread_mutex_unlock(&vars->meal);
				set_mutexed_var(&vars->is_dead, it[0] + 1, &vars->death);
				return ;
			}
			pthread_mutex_unlock(&vars->meal);
			pthread_mutex_lock(&vars->satiated_mutex);
			if (vars->phi[it[0]].satiated)
				it[1]++;
			pthread_mutex_unlock(&vars->satiated_mutex);
			it[0]++;
		}
		if (it[1] >= (size_t)vars->philo_count)
			return (set_mutexed_var(&vars->satiated, 1, &vars->satiated_mutex));
	}
}
