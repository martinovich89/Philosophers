/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:59:55 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/14 15:31:03 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

void	set_chrono(t_vars *vars)
{
	vars->chrono_start = get_current_time();
}
