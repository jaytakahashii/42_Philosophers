/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:32:27 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/25 18:32:02 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_finished(t_philos *philos)
{
	int	i;
	int	finished;
	t_conditions	conditions;

	i = 0;
	finished = 0;
	conditions = *philos[0].conditions;
	if (conditions.must_eat == -1)
		return (false);
	while (i < conditions.num_of_philos)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].finished)
			finished++;
		pthread_mutex_unlock(philos[i].eat_lock);
		i++;
	}
	if (finished == conditions.num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		philos[0].data->finished = true;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (true);
	}
	return (false);
}

bool	check_death(t_philos *philos)
{
	int	i;
	t_data	*data;
	t_conditions	conditions;

	i = 0;
	data = philos[0].data;
	conditions = *philos[0].conditions;
	while (i < conditions.num_of_philos)
	{
		pthread_mutex_lock(&data->eat_lock);
		if (get_time_in_ms() - philos[i].last_eat_time >= conditions.time_to_die && !philos[i].is_eating)
		{
			log_event(data, philos[i].id, "died");
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = true;
			pthread_mutex_unlock(&data->dead_lock);
			pthread_mutex_unlock(&data->eat_lock);
			return (true);
		}
		pthread_mutex_unlock(&data->eat_lock);
		i++;
	}
	return (false);
}

void	*program_observer(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (1)
	{
		if (check_death(philos))
		{
			printf("death\n");
			break ;
		}
		if (philos[0].conditions->must_eat != -1)
			continue ;
		if (check_finished(philos))
		{
			printf("finished\n");
			break ;
		}
	}
	return (arg);
}
