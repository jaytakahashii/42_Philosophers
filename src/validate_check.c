/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:00:36 by jtakahas          #+#    #+#             */
/*   Updated: 2024/08/24 17:14:57 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	set_conditions(int ac, char **av, t_conditions *conditions)
{
	if (!unsigned_long_atoi(av[1], &conditions->num_of_philos))
		return (false);
	if (!unsigned_long_atoi(av[2], &conditions->time_to_die))
		return (false);
	if (!unsigned_long_atoi(av[3], &conditions->time_to_eat))
		return (false);
	if (!unsigned_long_atoi(av[4], &conditions->time_to_sleep))
		return (false);
	if (ac == 6)
	{
		if (!unsigned_long_atoi(av[5], &conditions->num_of_times_to_eat))
			return (false);
	}
	else
		conditions->num_of_times_to_eat = 0;
	return (true);
}

bool	validate_check(int ac, char **av, t_conditions *conditions)
{
	if (ac != 5 && ac != 6)
	{
		error_message("Invalid number of arguments",
			"\nArgs: Philo TimeToDie TimeToEat TimeToSleep [NumOfTimesToEat]");
		return (false);
	}
	if (!set_conditions(ac, av, conditions))
		return (false);
	return (true);
}
