/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:20:38 by mhenry            #+#    #+#             */
/*   Updated: 2021/11/17 11:21:04 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>

int main(void)
{
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);
	printf("%zu.%zu\n", tv.tv_sec, tv.tv_usec);
	printf("%d\n", tz.tz_minuteswest);
}
