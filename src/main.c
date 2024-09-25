/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:45:33 by jay               #+#    #+#             */
/*   Updated: 2024/09/25 18:29:21 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thread_create(t_data *data, t_philos *philos, t_conditions conditions)
{
	int				i;
	pthread_t		monitor;

	if (pthread_create(&monitor, NULL, &program_observer, philos))
		return ;
	i = 0;
	while (i < conditions.num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &lifecycle, &philos[i]))
			return ;
		i += 2;
	}
	usleep(50);
	i = 1;
	while (i < conditions.num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, lifecycle, &data->philos[i]))
			return ;
		i += 2;
	}
	i = 0;
	if (pthread_join(monitor, NULL))
		return ;
	while (i < conditions.num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return ;
		i++;
	}
}

void	thread_destroy(t_data *data, t_conditions conditions)
{
	int	i;

	i = 0;
	while (i < conditions.num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->data_lock);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->dead_lock);
}

void	case_only_one_philo(t_data *data, t_conditions conditions)
{
	printf("%d %d %s\n", 0, 1, "is eating");
	ft_usleep(conditions.time_to_die);
	printf("%ld %d %s\n", conditions.time_to_die, 1, "died");
}

int	main(int argc, char **argv)
{
	t_conditions	conditions;
	t_data			data;
	t_philos		*philos;
	t_allocations	*allocations;

	allocations = NULL;
	if (!validate_and_get_conditions(argc, argv, &conditions))
		return (1);
	philos = malloc(sizeof(t_philos) * conditions.num_of_philos);
	if (!init_data(&data, philos, conditions, allocations)
		|| !init_philos(&data, philos, &conditions, allocations))
	{
		// free_allocations(&allocations);
		return (1);
	}
	if (conditions.num_of_philos == 1)
		case_only_one_philo(&data, conditions);
	else
	{
		thread_create(&data, philos, conditions);
		thread_destroy(&data, conditions);
	}
	// free_allocations(&allocations);
	return (0);
}
