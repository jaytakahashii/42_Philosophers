/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:45:33 by jay               #+#    #+#             */
/*   Updated: 2024/09/19 19:47:30 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_philosophers(void *arg)
{
	t_data	*data;
	unsigned long	count;

	data = (t_data *)arg;
	while (!data->stop_simulation)
	{
		count = 0;
		while (count < data->conditions.num_of_philos)
		{
			if (get_time_in_ms() - data->philos[count].last_meal_time
				> data->conditions.time_to_die)
			{
				log_event(data, data->philos[count].id, "died");
				data->stop_simulation = 1;
				break ;
			}
			count++;
		}
		usleep(1000);
	}
	return (NULL);
}


void	create_loop(t_data *data)
{
	unsigned long	count;
	pthread_t		monitor_thread;

	count = 0;
	pthread_create(&monitor_thread, NULL, monitor_philosophers, data);
	while (count < data->conditions.num_of_philos)
	{
		pthread_create(&data->philos[count].thread,
						NULL, philosopher_lifecycle, &data->philos[count]);
		count++;
	}
}

void	destroy_loop(t_data *data)
{
	unsigned long	count;

	count = 0;
	while (count < data->conditions.num_of_philos)
	{
		pthread_join(data->philos[count].thread, NULL);
		count++;
	}
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_allocations	*allocations;

	allocations = NULL;
	if (!validate_check(argc, argv, &data.conditions))
		return (1);
	if (!init_data(&data, allocations))
	{
		free_allocations(&allocations);
		return (1);
	}
	if (!init_philos(&data))
	{
		free_allocations(&allocations);
		return (1);
	}
	create_loop(&data);
	destroy_loop(&data);
	free_allocations(&allocations);
	return (0);
}
