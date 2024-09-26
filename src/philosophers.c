/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:45:30 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/26 17:12:27 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	dead_check(t_philos *philo)
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

void	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (dead_check(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	log_event(philo->central, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	if (dead_check(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	log_event(philo->central, philo->id, "has taken a fork");
	philo->is_eating = true;
	if (dead_check(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	log_event(philo->central, philo->id, "is eating");
	pthread_mutex_lock(&philo->central->eat_lock);
	pthread_mutex_lock(&philo->central->time_lock);
	philo->last_eat_time = get_time_in_ms() + philo->conditions->time_to_eat;
	pthread_mutex_unlock(&philo->central->time_lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->central->eat_lock);
	ft_usleep(philo->conditions->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(&philo->central->eat_lock);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->central->eat_lock);
}

void	philo_sleep(t_philos *philo)
{
	if (dead_check(philo))
		return ;
	log_event(philo->central, philo->id, "is sleeping");
	ft_usleep(philo->conditions->time_to_sleep);
}

void	philo_think(t_philos *philo)
{
	if (dead_check(philo))
		return ;
	log_event(philo->central, philo->id, "is thinking");
}

void	*lifecycle(void *arg)
{
	t_philos (*philos) = (t_philos *)arg;
	while (!dead_check(philos))
	{
		philo_eat(philos);
		philo_sleep(philos);
		philo_think(philos);

	}
	return (arg);
}
