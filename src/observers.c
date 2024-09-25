/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:32:27 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/25 18:00:50 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_finished(t_philos *philos)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (philos[0].conditions->must_eat == -1)
		return (false);
	while (i < philos[0].conditions->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].data->data_lock);
		if (philos[i].finished)
			finished++;
		pthread_mutex_unlock(&philos[i].data->data_lock);
		i++;
	}
	if (finished == philos[0].conditions->num_of_philos)
	{
		pthread_mutex_lock(&philos[0].data->data_lock);
		philos[0].data->finished = true;
		pthread_mutex_unlock(&philos[0].data->data_lock);
		return (true);
	}
	else
		return (false);
}

bool	check_death(t_philos *philos)
{
	int	i;
	t_data	*data;

	i = 0;
	data = philos[0].data;
	while (i < philos[0].conditions->num_of_philos)
	{
		pthread_mutex_lock(&data->data_lock);
		if (get_time_in_ms() - philos[i].last_eat_time > philos[i].conditions->time_to_die)
		{
			log_event(data, philos[i].id, "died");
			data->dead = true;
			pthread_mutex_unlock(&data->data_lock);
			return (true);
		}
		i++;
		pthread_mutex_unlock(&data->data_lock);
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
