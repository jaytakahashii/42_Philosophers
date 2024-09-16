/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:45:30 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/16 17:05:27 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// philosopher : eat -> sleep -> think -> eat -> sleep -> think -> ...

void	philo_sleep(t_philos *philosopher, t_table *table, t_conditions conditions)
{
	printf("%d %d is Sleeping\n", philosopher->global_time, philosopher->id + 1);
	usleep(conditions.time_to_sleep * 1000);
	philosopher->global_time += conditions.time_to_sleep;
	table->state[philosopher->id] = THINKING;
}

void	philo_eat(t_philos *philosopher, t_table *table, t_conditions conditions)
{
	int	LEFT;
	int	RIGHT;

	LEFT = (philosopher->id + table->num_philosophers - 1) % table->num_philosophers;
	RIGHT = (philosopher->id + 1) % table->num_philosophers;
	if (table->state[philosopher->id] == THINKING &&
		table->state[LEFT] != EATING &&
		table->state[RIGHT] != EATING)
	{
		pthread_mutex_lock(&table->mutex);
		table->state[philosopher->id] = EATING;
		printf("%d %d is Eating\n", philosopher->global_time, philosopher->id + 1);
		usleep(conditions.time_to_eat * 1000);
		philosopher->global_time += conditions.time_to_eat;
		table->state[philosopher->id] = SLEEPING;
		pthread_mutex_unlock(&table->mutex);
	}
}

void	*philosopher_loop(void *philo)
{
	t_philos	*philosopher;
	t_table		*table;
	t_conditions	conditions;

	philosopher = (t_philos *)philo;
	table = philosopher->table;
	conditions = table->conditions;
	while (1)
	{
		philo_eat(philosopher, table, conditions);
		philo_sleep(philosopher, table, conditions);
		printf("Philosopher %d is thinking\n", philosopher->id + 1);
	}
	return (NULL);
}