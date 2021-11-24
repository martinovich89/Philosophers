/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floattimeofday.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:20:35 by mhenry            #+#    #+#             */
/*   Updated: 2021/11/17 11:21:04 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>

int main(void)
{
	struct timeval tv;
	struct timeval tz;
	double time;

	gettimeofday(&tv, &tz);
	time = (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
	printf("%lf\n", time);
}
