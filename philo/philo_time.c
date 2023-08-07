/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <omarchic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:44:43 by omarchic          #+#    #+#             */
/*   Updated: 2023/08/06 17:44:51 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000 + te.tv_usec / 1000;
	return (milliseconds);
}

int	ft_usleep(long long microseconds)
{
	long long	i;
	long long	k;
	long long	l;

	i = 0;
	k = timestamp();
	l = k;
	while (timestamp() <= l + microseconds)
		usleep(100);
	return (0);
}
