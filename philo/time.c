/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:29:03 by mhenry            #+#    #+#             */
/*   Updated: 2022/02/14 15:33:21 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

size_t	get_current_time(void)
{
	size_t			time;
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	time = tv.tv_sec * 1000000 + tv.tv_usec;
	return (time);
}

int	my_usleep(size_t time, struct timeval *tv, struct timezone *tz)
{
	double	oldtime;
	double	newtime;
	double	time_f;

	gettimeofday(tv, tz);
	time_f = (double)time / 1000000;
	oldtime = (double)tv->tv_sec + (double)tv->tv_usec / 1000000;
	newtime = oldtime;
	while (newtime - oldtime < time_f)
	{
		usleep(200);
		if (!gettimeofday(tv, tz))
			return (-1);
		newtime = (double)tv->tv_sec + (double)tv->tv_usec / 1000000;
	}
	return (0);
}

int	timetostr(char *str, size_t elapsed_time)
{
	int		ret;
	size_t	n;
	size_t	i;

	i = (elapsed_time == 0);
	n = elapsed_time;
	while (str[i])
		i++;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	ret = (int)i;
	if (elapsed_time == 0)
		return (ft_strcat(str, "0"));
	str[i + 1] = '\0';
	while (elapsed_time > 0)
	{
		i--;
		str[i] = elapsed_time % 10 + '0';
		elapsed_time /= 10;
	}
	return (ret);
}

int	sleep_until(t_phi *phi, size_t time_to_stop)
{
	(void)phi;
	while (get_current_time() < time_to_stop)
	{
		pthread_mutex_lock(&phi->vars->death);
		if (phi->vars->is_dead)
			return (unlock_before_return(&phi->vars->death, NULL));
		pthread_mutex_unlock(&phi->vars->death);
		usleep(100);
	}
	return (0);
}

int	wait_for_death(t_phi *phi)
{
	pthread_mutex_unlock(phi->first_fork);
	sleep_until(phi, ~0);
	update_status(phi, 4);
	print_status(phi, &phi->vars->print, &phi->vars->death);
	return (1);
}
