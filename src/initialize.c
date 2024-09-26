/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:07:20 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/26 17:04:03 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_philos(t_central *central, t_philos *philos, t_conditions *conditions)
{
	__uint64_t i = 0;

	if (!philos)
		return (false);
	while (i < conditions->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].is_eating = false;
		philos[i].eat_count = 0;
		philos[i].conditions = conditions;
		philos[i].start_time = get_time_in_ms();
		philos[i].last_eat_time = get_time_in_ms();
		philos[i].dead = &central->dead_flag;
		philos[i].central = central;
		philos[i].print_lock = &central->print_lock;
		philos[i].eat_lock = &central->eat_lock;
		philos[i].dead_lock = &central->dead_lock;
		philos[i].time_lock = &central->time_lock;
		philos[i].l_fork = &central->forks[i];
		if (i == 0)
			philos[i].r_fork = &central->forks[conditions->num_of_philos - 1];
		else
			philos[i].r_fork = &central->forks[i - 1];
		i++;
	}
	return (true);
}

bool	init_data(t_central *data, t_philos *philos, t_conditions conditions)
{
	data->dead_flag = false;
	data->finished = false;
	data->philos = philos;
	data->forks = malloc(sizeof(pthread_mutex_t) * conditions.num_of_philos);
	if (!data->forks)
		return (false);
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (false);
	if (pthread_mutex_init(&data->eat_lock, NULL))
		return (false);
	if (pthread_mutex_init(&data->dead_lock, NULL))
		return (false);
	if (pthread_mutex_init(&data->time_lock, NULL))
		return (false);
	return (true);
}