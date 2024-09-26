/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:32:27 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/26 20:16:15 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	finish_check(t_philos *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->finish)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (false);
}

static bool	check_finished(t_philos *philo)
{
	uint64_t		i;
	uint64_t		finished;
	t_conditions	conditions;

	i = 0;
	finished = 0;
	conditions = *philo[0].conditions;
	if (conditions.must_eat == 0)
		return (false);
	while (i < conditions.num_of_philos)
	{
		pthread_mutex_lock(philo[i].eat_lock);
		if (philo[i].eat_count >= conditions.must_eat)
			finished++;
		pthread_mutex_unlock(philo[i].eat_lock);
		i++;
	}
	if (finished == conditions.num_of_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->finish = true;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (true);
	}
	return (false);
}

static bool	philosopher_dead(t_philos *philo, uint64_t time_to_die)
{
	pthread_mutex_lock(philo->eat_lock);
	if (get_time_in_ms() - philo->last_eat_time >= time_to_die)
	{
		pthread_mutex_unlock(philo->eat_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->eat_lock);
	return (false);
}

static bool	check_death(t_philos *philo)
{
	uint64_t		i;
	t_central		*cent;
	t_conditions	conditions;

	i = 0;
	cent = philo[0].central;
	conditions = *philo[0].conditions;
	while (i < conditions.num_of_philos)
	{
		if (philosopher_dead(&philo[i], conditions.time_to_die))
		{
			pthread_mutex_lock(&cent->dead_lock);
			*philo->finish = true;
			pthread_mutex_unlock(&cent->dead_lock);
			log_event(cent, philo[i].id, "died");
			return (true);
		}
		i++;
	}
	return (false);
}

void	*philos_observer(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (1)
	{
		if (check_death(philos) || check_finished(philos))
			break ;
	}
	return (arg);
}
