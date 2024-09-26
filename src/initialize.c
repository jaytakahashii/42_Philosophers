/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:07:20 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/26 19:52:32 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	conditions_init(t_conditions *conditions)
{
	conditions->num_of_philos = 0;
	conditions->time_to_die = 0;
	conditions->time_to_eat = 0;
	conditions->time_to_sleep = 0;
	conditions->must_eat = 0;
}

bool	init_philos(t_central *cent, t_philos *philos, t_conditions *cond)
{
	uint64_t (i) = 0;
	if (!philos)
		return (false);
	while (i < cond->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].is_eating = false;
		philos[i].eat_count = 0;
		philos[i].conditions = cond;
		philos[i].start_time = get_time_in_ms();
		philos[i].last_eat_time = get_time_in_ms();
		philos[i].finish = &cent->finish;
		philos[i].central = cent;
		philos[i].print_lock = &cent->print_lock;
		philos[i].eat_lock = &cent->eat_lock;
		philos[i].dead_lock = &cent->dead_lock;
		philos[i].l_fork = &cent->forks[i];
		if (i == 0)
			philos[i].r_fork = &cent->forks[cond->num_of_philos - 1];
		else
			philos[i].r_fork = &cent->forks[i - 1];
		i++;
	}
	return (true);
}

bool	init_central(t_central *cent, t_philos *philos, t_conditions conditions)
{
	cent->finish = false;
	cent->philos = philos;
	cent->forks = malloc(sizeof(pthread_mutex_t) * conditions.num_of_philos);
	if (!cent->forks)
	{
		error_message("Malloc failed", NULL);
		free(philos);
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
