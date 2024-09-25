/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:00:36 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/25 18:00:50 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	get_conditions(int ac, char **av, t_conditions *conditions)
{
	conditions->num_of_philos = 0;
	conditions->time_to_die = 0;
	conditions->time_to_eat = 0;
	conditions->time_to_sleep = 0;
	conditions->must_eat = 0;
	if (!is_atoi(av[1], &conditions->num_of_philos))
		return (false);
	if (!is_uint_atoi(av[2], &conditions->time_to_die))
		return (false);
	if (!is_uint_atoi(av[3], &conditions->time_to_eat))
		return (false);
	if (!is_uint_atoi(av[4], &conditions->time_to_sleep))
		return (false);
	if (ac == 6)
	{
		if (!is_atoi(av[5], &conditions->must_eat))
			return (false);
	}
	else
		conditions->must_eat = -1;
	return (true);
}

bool	validate_and_get_conditions(int ac, char **av, t_conditions *conditions)
{
	if (ac != 5 && ac != 6)
	{
		error_message("Invalid number of arguments",
			"\nArgs: Philo TimeToDie TimeToEat TimeToSleep [NumOfTimesToEat]");
		return (false);
	}
	if (!get_conditions(ac, av, conditions))
		return (false);
	return (true);
}
