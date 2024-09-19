/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:07:20 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/19 19:36:38 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_philos(t_data *data)
{
	unsigned long (i) = 0;
	while (i < data->conditions.num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1)
			% data->conditions.num_of_philos];
		data->philos[i].is_eating = false;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		i++;
	}
	return (true);
}

bool	init_data(t_data *data, t_allocations *allocations)
{
	unsigned long (count) = 0;
	data->stop_simulation = 0;
	data->start_time = get_time_in_ms();
	data->forks = ft_malloc(data->conditions.num_of_philos
							* sizeof(pthread_mutex_t), &allocations);
	if (!data->forks)
		return (false);
	data->philos = ft_malloc(data->conditions.num_of_philos
							* sizeof(t_philos), &allocations);
	if (!data->philos)
		return (false);

	pthread_mutex_init(&data->print_lock, NULL);
	while (count < data->conditions.num_of_philos)
	{
		pthread_mutex_init(&data->forks[count], NULL);
		count++;
	}
	return (true);
}
