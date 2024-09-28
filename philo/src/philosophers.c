/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:45:30 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/28 13:08:26 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	get_fork(t_philos *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (finish_check(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	log_event(philo->central, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	if (finish_check(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (false);
	}
	log_event(philo->central, philo->id, "has taken a fork");
	return (true);
}

static void	philo_eat(t_philos *philo)
{
	if (!get_fork(philo))
		return ;
	if (finish_check(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	log_event(philo->central, philo->id, "is eating");
	pthread_mutex_lock(&philo->central->eat_lock);
	philo->last_eat_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->central->eat_lock);
	ft_usleep(philo->conditions->time_to_eat);
	pthread_mutex_lock(&philo->central->eat_lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->central->eat_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	philo_sleep(t_philos *philo)
{
	if (finish_check(philo))
		return ;
	log_event(philo->central, philo->id, "is sleeping");
	ft_usleep(philo->conditions->time_to_sleep);
}

static void	philo_think(t_philos *philo)
{
	if (finish_check(philo))
		return ;
	log_event(philo->central, philo->id, "is thinking");
}

void	*lifecycle(void *arg)
{
	t_philos (*philos) = (t_philos *)arg;
	while (!finish_check(philos))
	{
		philo_eat(philos);
		philo_sleep(philos);
		philo_think(philos);
	}
	return (arg);
}
