/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:07:20 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/25 18:00:36 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_philos(t_data *data, t_philos *philos, t_conditions *conditions, t_allocations *allocations)
{
	int i = 0;

	// philos = ft_malloc((sizeof(t_philos) * conditions->num_of_philos), &allocations);
	if (!philos)
		return (false);
	while (i < conditions->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].conditions = conditions;
		philos[i].start_time = get_time_in_ms();
		philos[i].last_eat_time = get_time_in_ms();
		philos[i].eat_count = 0;
		philos[i].finished = false;
		philos[i].data = data;
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
	data->dead = false;
	data->finished = false;
	data->philos = philos;
	// data->forks = ft_malloc(sizeof(pthread_mutex_t) * conditions.num_of_philos, &allocations);
	data->forks = malloc(sizeof(pthread_mutex_t) * conditions.num_of_philos);
	if (!data->forks)
		return (false);
	if (pthread_mutex_init(&data->data_lock, NULL))
		return (false);
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (false);
	return (true);
}