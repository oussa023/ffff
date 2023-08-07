/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <omarchic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:42:01 by omarchic          #+#    #+#             */
/*   Updated: 2023/08/06 23:24:38 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		print_mutex(s_philo *s, char *str, long long time, int philo)
{
	pthread_mutex_lock(&s->print_mute);
	printf("%lldms    Philosopher %d %s\n", time, philo, str);
	if (strcmp(str, "died"))
		pthread_mutex_unlock(&s->print_mute);
	else
	{
		philo_free(s);
		return(0);
	}
	return(1);
}

void	mutex_init(s_philo *s)
{
	s->i = 0;
	pthread_mutex_init(&s->print_mute, NULL);
	while (s->i < s->philo_num)
	{
		pthread_mutex_init(&s->forks[s->i], NULL);
		pthread_mutex_init(&s->mutex_ate[s->i], NULL);
		pthread_mutex_init(&s->times[s->i], NULL);
		s->i++;
	}
}

void	mutex_destroy(s_philo *s)
{
	s->i = 0;
	while (s->i < s->philo_num)
	{
		pthread_mutex_destroy(&s->forks[s->i]);
		pthread_mutex_destroy(&s->mutex_ate[s->i]);
		pthread_mutex_destroy(&s->times[s->i]);
		s->i++;
	}
}
