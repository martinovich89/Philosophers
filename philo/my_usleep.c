/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:20:31 by mhenry            #+#    #+#             */
/*   Updated: 2021/11/18 14:14:46 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

void	my_usleep(size_t time, struct timeval *tv, struct timezone *tz)
{
	double	oldtime;
	double	newtime;
	double	time_f;

	time_f = (double)time / 1000000;
	oldtime = (double)tv->tv_sec + (double)tv->tv_usec / 1000000;
	newtime = oldtime;
	while (newtime - oldtime < time_f)
	{
		usleep(100);
		if (!gettimeofday(tv, tz))
			return (ft_error("failed to get time of day"));
		newtime = (double)tv->tv_sec + (double)tv->tv_usec / 1000000;
	}
}

int main(void)
{
	struct	timeval tv;
	struct	timezone tz;
	double	time;
	double	my_time;
	double	before;
	double	after;
	int		i;

	gettimeofday(&tv, &tz);
	before = (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
	my_usleep(1000, &tv, &tz);
	after = (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
	my_time = after - before;
	printf("---------\n%lf\n%lf\n%lf\n---------\n", my_time, after, before);
	gettimeofday(&tv, &tz);
	before = (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
	i = 0;
	while (i < 100)
	{
		usleep(1000);
		i++;
	}
	gettimeofday(&tv, &tz);
	after = (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
	printf("%lf\n", after - before);

	gettimeofday(&tv, &tz);
	before = (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
	usleep(1000);
	gettimeofday(&tv, &tz);
	after = (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
	time = after - before;
	printf("%lf\n", after - before);
}
