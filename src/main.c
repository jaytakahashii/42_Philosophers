/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:45:33 by jay               #+#    #+#             */
/*   Updated: 2024/09/16 16:55:51 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_table(t_table *table, t_allocations *allocations)
{
	size_t	count;

	table->state = ft_malloc(table->conditions.num_of_philos * sizeof(int), &allocations);
	if (!table->state)
		return (false);
	table->forks = ft_malloc(table->conditions.num_of_philos * sizeof(pthread_mutex_t), &allocations);
	if (!table->forks)
		return (false);
	table->num_philosophers = table->conditions.num_of_philos;
	pthread_mutex_init(&table->mutex, NULL);
	count = 0;
	while (count < table->conditions.num_of_philos)
	{
		table->state[count] = THINKING;
		pthread_mutex_init(&table->forks[count], NULL);
		count++;
	}
	return (true);
}

void	mutex_loop(t_table *table, t_philos *philos, pthread_t *thread_id)
{
	size_t	count;

	count = 0;
	philos->global_time = 0;
	while (count < table->conditions.num_of_philos)
	{
		philos[count].id = count;
		philos[count].table = table;
		pthread_create(&thread_id[count], NULL, philosopher_loop, &philos[count]);
		count++;
	}
	count = 0;
	while (count < table->conditions.num_of_philos)
	{
		pthread_join(thread_id[count], NULL);
		count++;
	}
}

void	destroy_table(t_table *table)
{
	size_t	count;

	count = 0;
	while (count < table->conditions.num_of_philos)
	{
		pthread_mutex_destroy(&table->forks[count]);
		count++;
	}
	pthread_mutex_destroy(&table->mutex);
}

int	main(int argc, char **argv)
{
	t_table			table;
	pthread_t		*thread_id;
	t_philos		*philos;
	t_allocations	*allocations;

	allocations = NULL;
	philos = NULL;
	if (!validate_check(argc, argv, &table.conditions))
		return (1);
	thread_id = ft_malloc(table.conditions.num_of_philos * sizeof(pthread_t),
			&allocations);
	if (!thread_id)
		return (1);
	philos = ft_malloc(table.conditions.num_of_philos * sizeof(t_philos),
			&allocations);
	if (!philos)
		return (1);
	if (!init_table(&table, allocations))
		return (1);
	mutex_loop(&table, philos, thread_id);
	destroy_table(&table);
	free_allocations(&allocations);
	return (0);
}
