/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:07:20 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/25 18:59:23 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_philos(t_data *data, t_philos *philos, t_conditions *conditions, t_allocations *allocations)
{
	int i = 0;

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
		philos[i].finished = &data->finished;
		philos[i].dead = &data->dead_flag;
		philos[i].data = data;
		philos[i].print_lock = &data->print_lock;
		philos[i].eat_lock = &data->eat_lock;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].time_lock = &data->time_lock;
		philos[i].l_fork = &data->forks[i];
		if (i == 0)
			philos[i].r_fork = &data->forks[conditions->num_of_philos - 1];
		else
			philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (true);
}

bool	init_data(t_data *data, t_philos *philos, t_conditions conditions, t_allocations *allocations)
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