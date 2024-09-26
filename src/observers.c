/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:32:27 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/26 18:12:10 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	dead_check(t_philos *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (false);
}

bool	check_finished(t_philos *philos)
{
	uint64_t		i;
	uint64_t		finished;
	t_conditions	conditions;

	i = 0;
	finished = 0;
	conditions = *philos[0].conditions;
	if (conditions.must_eat == 0)
		return (false);
	while (i < conditions.num_of_philos)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].eat_count >= conditions.must_eat)
			finished++;
		pthread_mutex_unlock(philos[i].eat_lock);
		i++;
	}
	if (finished == conditions.num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = true;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (true);
	}
	return (false);
}

bool	philosopher_dead(t_philos *philo, uint64_t time_to_die)
{
	pthread_mutex_lock(philo->eat_lock);
	if (get_time_in_ms() - philo->last_eat_time >= time_to_die
		&& !philo->is_eating)
	{
		pthread_mutex_unlock(philo->eat_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->eat_lock);
	return (false);
}

bool	check_death(t_philos *philos)
{
	uint64_t		i;
	t_central		*data;
	t_conditions	conditions;

	i = 0;
	data = philos[0].central;
	conditions = *philos[0].conditions;
	while (i < conditions.num_of_philos)
	{
		if (philosopher_dead(&philos[i], conditions.time_to_die))
		{
			pthread_mutex_lock(&data->dead_lock);
			*philos->dead = true;
			pthread_mutex_unlock(&data->dead_lock);
			log_event(data, philos[i].id, "died");
			return (true);
		}
		i++;
	}
	return (false);
}

void	*program_observer(void *arg)
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
