/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:45:33 by jay               #+#    #+#             */
/*   Updated: 2024/09/26 20:00:37 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	philos_thread_create(t_philos *philo, t_conditions *cond)
{
	uint64_t	i;

	i = 0;
	while (i < cond->num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, lifecycle, &philo[i]))
			return (false);
		i += 2;
	}
	usleep(50);
	i = 1;
	while (i < cond->num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, lifecycle, &philo[i]))
			return (false);
		i += 2;
	}
	return (true);
}

static void	thread_create(t_central *cent, t_philos *philo, t_conditions cond)
{
	pthread_t	monitor;
	uint64_t	i;

	if (pthread_create(&monitor, NULL, &philos_observer, philo)
		|| !philos_thread_create(philo, &cond))
	{
		error_message("Thread creation failed", NULL);
		return ;
	}
	if (pthread_join(monitor, NULL))
		return ;
	i = 0;
	while (i < cond.num_of_philos)
	{
		if (pthread_join(cent->philos[i].thread, NULL))
			return ;
		i++;
	}
}

static void	thread_destroy(t_central *cent, t_conditions cond)
{
	uint64_t	i;

	i = 0;
	while (i < cond.num_of_philos)
	{
		pthread_mutex_destroy(&cent->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&cent->print_lock);
	pthread_mutex_destroy(&cent->eat_lock);
	pthread_mutex_destroy(&cent->dead_lock);
}

static void	case_only_one_philo(t_conditions cond)
{
	printf("%d %d %s\n", 0, 1, "is eating");
	ft_usleep(cond.time_to_die);
	printf("%" PRIu64 " %d %s\n", cond.time_to_die, 1, "died");
}

int	main(int argc, char **argv)
{
	t_conditions	conditions;
	t_central		central;
	t_philos		*philos;

	conditions_init(&conditions);
	if (!validate_and_get_conditions(argc, argv, &conditions))
		return (1);
	philos = malloc(sizeof(t_philos) * conditions.num_of_philos);
	if (!philos)
	{
		error_message("Malloc failed", NULL);
		return (1);
	}
	if (!init_central(&central, philos, conditions)
		|| !init_philos(&central, philos, &conditions))
		return (1);
	if (conditions.num_of_philos == 1)
		case_only_one_philo(conditions);
	else
	{
		thread_create(&central, philos, conditions);
		thread_destroy(&central, conditions);
	}
	return (free(philos), free(central.forks), 0);
}
