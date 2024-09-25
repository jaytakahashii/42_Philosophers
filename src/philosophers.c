/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:45:30 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/25 18:38:24 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// philosopher : eat -> sleep -> think -> eat -> sleep -> think -> ...
void	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(philo->r_fork);
	log_event(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	log_event(philo->data, philo->id, "has taken a fork");
	philo->is_eating = true;
	log_event(philo->data, philo->id, "is eating");
	pthread_mutex_lock(&philo->data->eat_lock);
	pthread_mutex_lock(&philo->data->data_lock);
	philo->last_eat_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->data_lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	ft_usleep(philo->conditions->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->data->eat_lock);
}

void	philo_sleep(t_philos *philo)
{
	log_event(philo->data, philo->id, "is sleeping");
	ft_usleep(philo->conditions->time_to_sleep);
}

void	philo_think(t_philos *philo)
{
	log_event(philo->data, philo->id, "is thinking");
}

void	*lifecycle(void *arg)
{
	t_philos (*philos) = (t_philos *)arg;
	while (philos->data->finished == false && philos->data->dead_flag == false)
	{
		philo_eat(philos);
		philo_sleep(philos);
		philo_think(philos);

	}
	return (arg);
}
