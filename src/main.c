/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:45:33 by jay               #+#    #+#             */
/*   Updated: 2024/09/26 17:03:12 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thread_create(t_central *central, t_philos *philos, t_conditions conditions)
{
	__uint64_t	i;
	pthread_t	monitor;

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
		if (pthread_create(&philos[i].thread, NULL, lifecycle, &central->philos[i]))
			return ;
		i += 2;
	}
	i = 0;
	if (pthread_join(monitor, NULL))
		return ;
	while (i < conditions.num_of_philos)
	{
		if (pthread_join(central->philos[i].thread, NULL))
			return ;
		i++;
	}
}

void	thread_destroy(t_central *central, t_conditions conditions)
{
	__uint64_t	i;

	i = 0;
	while (i < conditions.num_of_philos)
	{
		pthread_mutex_destroy(&central->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&central->time_lock);
	pthread_mutex_destroy(&central->print_lock);
	pthread_mutex_destroy(&central->eat_lock);
	pthread_mutex_destroy(&central->dead_lock);
}

void	case_only_one_philo(t_conditions conditions)
{
	printf("%d %d %s\n", 0, 1, "is eating");
	ft_usleep(conditions.time_to_die);
	printf("%ld %d %s\n", conditions.time_to_die, 1, "died");
}

int	main(int argc, char **argv)
{
	t_conditions	conditions; // 条件（コマンドライン引数）
	t_central			central; // 全体のデータ
	t_philos		*philos; // 哲学者一人ひとりのデータ
	t_allocations	*allocations; // メモリ確保の情報

	allocations = NULL;
	if (!validate_and_get_conditions(argc, argv, &conditions))
		return (1);
	philos = malloc(sizeof(t_philos) * conditions.num_of_philos);
	if (!init_data(&central, philos, conditions)
		|| !init_philos(&central, philos, &conditions))
	{
		// free_allocations(&allocations);
		return (1);
	}
	if (conditions.num_of_philos == 1)
		case_only_one_philo(conditions);
	else
	{
		thread_create(&central, philos, conditions);
		thread_destroy(&central, conditions);
	}
	// free_allocations(&allocations);
	return (0);
}
