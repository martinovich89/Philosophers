/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:19:57 by mhenry            #+#    #+#             */
/*   Updated: 2021/11/17 11:56:19 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s2[i] - s1[i]);
}

int		ft_atoi(char *str)
{
	size_t	i;
	int		sign;
	size_t	nb;

	if (ft_strcmp(str, "-2147483648") == 0)
		return (-2147483648);
	nb = 0;
	sign = (str[0] != '-') * 2 - 1;
	i = (str[0] == '-');
	while (str[i])
	{
		if (nb > 2147483647)
			return (-1);
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	return ((int)nb * sign);
}