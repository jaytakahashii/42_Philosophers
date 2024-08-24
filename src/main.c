/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:45:33 by jay               #+#    #+#             */
/*   Updated: 2024/08/24 17:51:09 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_conditions	conditions;
	t_allocations	*allocations;
	pthread_mutex_t	mutex;

	allocations = NULL;
	if (!validate_check(argc, argv, &conditions))
		return (1);
	printf("Philo: %lu\nTimeToDie: %lu\nTimeToEat: %lu\nTimeToSleep: \
		%lu\nNumOfTimesToEat: %lu\n",
		conditions.num_of_philos, conditions.time_to_die,
		conditions.time_to_eat, conditions.time_to_sleep,
		conditions.num_of_times_to_eat);
	free_allocations(&allocations);
	return (0);
}
