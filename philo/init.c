/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:38:43 by omarchic          #+#    #+#             */
/*   Updated: 2023/08/06 17:38:47 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_create(s_philo *s)
{
	int	i;

	i = 0;
	while (i < s->philo_num)
	{
		pthread_create(&s->philos[i], NULL, (void *)func, s);
		pthread_detach(s->philos[i]);
		usleep(100);
		i++;
	}
}

void	philo_init(s_philo *s, int ac, char **av)
{
	long long	fofo;

	fofo = timestamp();
	s->philo_num = atoi(av[1]);
	s->time_to_die = atoi(av[2]);
	s->time_to_eat = atoi(av[3]);
	s->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		s->eat_x_times = atoi(av[5]);
	s->philos = (pthread_t *)malloc(sizeof(pthread_t) * s->philo_num);
	s->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* s->philo_num);
	s->mutex_ate = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* s->philo_num);
	s->times = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* s->philo_num);
	s->last_time_ate = malloc(sizeof(long long) * s->philo_num);
	s->eat_times = malloc(sizeof(long long) * s->philo_num);
	s->i = 0;
	s->start = fofo;
	while (s->i < s->philo_num)
	{
		s->last_time_ate[s->i] = fofo;
		s->eat_times[s->i] = 0;
		s->i++;
	}
}
