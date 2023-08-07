/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarchic <omarchic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:39:53 by omarchic          #+#    #+#             */
/*   Updated: 2023/08/06 23:28:13 by omarchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_death(s_philo *s)
{
	int			i;
	long long	j;

	i = 0;
	j = timestamp();
	while (i < s->i)
	{
		pthread_mutex_lock(&s->mutex_ate[i]);
		if (j - s->last_time_ate[i] >= s->time_to_die)
		{
			if (print_mutex(s, "died", j - s->start, i) == 0)
				return(0);
		}
		pthread_mutex_unlock(&s->mutex_ate[i]);
		i++;
	}
	return(1);
}

int		check_all_ate(s_philo *s, int ac, char **av)
{
	int	i;

	i = 0;
	while (i < s->i)
	{
		if (ac == 6 && (all_philos_ate_x_times(s, atoi(av[1]),
					atoi(av[5])) == 1))
		{
			philo_free(s);
			return(0);
		}
		i++;
	}
	return(1);
}

int		check(s_philo *s, int ac, char **av)
{
	if (check_death(s) == 0 || check_all_ate(s, ac, av) == 0)
		return(0);
	return(1);
}
