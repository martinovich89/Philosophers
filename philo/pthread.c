/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:20:14 by mhenry            #+#    #+#             */
/*   Updated: 2021/11/17 11:21:04 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <pthread.h>

pthread_t		thread[10];
pthread_mutex_t	mutex[10];
int				primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

typedef struct s_vars
{
	size_t			id;
}	t_vars;


void	*routine(void *arg)
{
	size_t i;

	i = *(size_t *)arg;
	pthread_mutex_lock(mutex + i);
	printf("%d\n", primes[i]);
	pthread_mutex_unlock(mutex + i);
	return (NULL);
}

int main(void)
{
	size_t			i;
	t_vars			vars[10];
	
	i = 0;
	while (i < 10)
	{
		vars[i].id = i;
		pthread_mutex_init(&mutex[i], NULL);
		pthread_create(&thread[i], NULL, &routine, &vars[i].id);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	printf("%d\n", BUFFERSIZE);
	return (0);
}
