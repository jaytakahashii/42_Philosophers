/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:07:20 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/26 20:04:04 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_conditions(t_conditions *cond)
{
	cond->num_of_philos = 0;
	cond->time_to_die = 0;
	cond->time_to_eat = 0;
	cond->time_to_sleep = 0;
	cond->must_eat = 0;
}

bool	init_philos(t_central *cent, t_philos *philo, t_conditions *cond)
{
	uint64_t (i) = 0;
	if (!philo)
		return (false);
	while (i < cond->num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].is_eating = false;
		philo[i].eat_count = 0;
		philo[i].conditions = cond;
		philo[i].start_time = get_time_in_ms();
		philo[i].last_eat_time = get_time_in_ms();
		philo[i].finish = &cent->finish;
		philo[i].central = cent;
		philo[i].print_lock = &cent->print_lock;
		philo[i].eat_lock = &cent->eat_lock;
		philo[i].dead_lock = &cent->dead_lock;
		philo[i].l_fork = &cent->forks[i];
		if (i == 0)
			philo[i].r_fork = &cent->forks[cond->num_of_philos - 1];
		else
			philo[i].r_fork = &cent->forks[i - 1];
		i++;
	}
	return (true);
}

bool	init_central(t_central *cent, t_philos *philo, t_conditions cond)
{
	cent->finish = false;
	cent->philos = philo;
	cent->forks = malloc(sizeof(pthread_mutex_t) * cond.num_of_philos);
	if (!cent->forks)
	{
		error_message("Malloc failed", NULL);
		free(philo);
		return (false);
	}
	if (pthread_mutex_init(&cent->print_lock, NULL)
		|| pthread_mutex_init(&cent->eat_lock, NULL)
		|| pthread_mutex_init(&cent->dead_lock, NULL))
	{
		error_message("Mutex init failed", NULL);
		return (false);
	}
	return (true);
}
