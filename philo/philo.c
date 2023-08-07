/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <omarchic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:55:08 by omarchic          #+#    #+#             */
/*   Updated: 2023/08/06 23:21:41 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philos_ate_x_times(s_philo *s, int num_philo, int times_to_eat)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (i < num_philo)
	{
		pthread_mutex_lock(&s->times[i]);
		if (s->eat_times[i] >= times_to_eat)
			index++;
		pthread_mutex_unlock(&s->times[i]);
		i++;
	}
	if (index == num_philo)
		return (1);
	return (0);
}

void	philo_free(s_philo *s)
{
	free(s->philos);
	free(s->forks);
	free(s->mutex_ate);
	free(s->times);
	free(s->last_time_ate);
	free(s->eat_times);
}

void	*func(s_philo *philo)
{
	int	n;

	n = philo->i;
	while (1)
	{
		pthread_mutex_lock(&philo->forks[n]);
		printf("%lldms Philosopher %d has taken a fork\n", timestamp()
				- philo->start, n);
		pthread_mutex_lock(&philo->forks[(n + 1) % (philo->philo_num)]);
		printf("%lldms Philosopher %d has taken a fork\n", timestamp()
				- philo->start, n);
		pthread_mutex_lock(&philo->times[n]);
		philo->eat_times[n]++;
		pthread_mutex_unlock(&philo->times[n]);
		pthread_mutex_lock(&philo->mutex_ate[n]);
		philo->last_time_ate[n] = timestamp();
		printf("%lldms Philosopher %d is eating\n", philo->last_time_ate[n]
				- philo->start, n);
		pthread_mutex_unlock(&philo->mutex_ate[n]);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->forks[n]);
		pthread_mutex_unlock(&philo->forks[(n + 1) % (philo->philo_num)]);
		printf("%lldms Philosopher %d is sleeping\n", timestamp()
				- philo->start, n);
		ft_usleep(philo->time_to_sleep);
		printf("%lldms Philosopher %d is thinking\n", timestamp()
				- philo->start, n);
	}
	return (NULL);
}

int	parse(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	s_philo	s;

	if (ac == 5 || ac == 6)
	{
		if (parse(ac, av) == 0)//exit was here
			return(0);
		philo_init(&s, ac, av);
		mutex_init(&s);
		// thread_create(&s);
		s.i = 0;
		while (s.i < s.philo_num)
		{
			pthread_create(&s.philos[s.i], NULL, (void *)func, &s);
			pthread_detach(s.philos[s.i]);
			usleep(100);
			s.i++;
		}
		while (1)
		{
			if (check(&s, ac, av) == 0)
				return(0);
		}
		mutex_destroy(&s);
		return (0);
	}
}
