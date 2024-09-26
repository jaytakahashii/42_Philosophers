/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:00:36 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/26 19:58:46 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_zero(uint64_t num)
{
	if (num == 0)
	{
		error_message("Invalid argument", ": 0 is not allowed");
		return (true);
	}
	return (false);
}

static bool	get_conditions(int ac, char **av, t_conditions *cond)
{
	if (!is_uint_atoi(av[1], &cond->num_of_philos)
		|| is_zero(cond->num_of_philos))
		return (false);
	if (!is_uint_atoi(av[2], &cond->time_to_die)
		|| is_zero(cond->time_to_die))
		return (false);
	if (!is_uint_atoi(av[3], &cond->time_to_eat)
		|| is_zero(cond->time_to_eat))
		return (false);
	if (!is_uint_atoi(av[4], &cond->time_to_sleep)
		|| is_zero(cond->time_to_sleep))
		return (false);
	if (ac == 6)
	{
		if (!is_uint_atoi(av[5], &cond->must_eat)
			|| is_zero(cond->must_eat))
			return (false);
	}
	else
		cond->must_eat = 0;
	return (true);
}

bool	validate_and_get_conditions(int ac, char **av, t_conditions *cond)
{
	if (ac != 5 && ac != 6)
	{
		error_message("Invalid number of arguments",
			"\nArgs: Philo TimeToDie TimeToEat TimeToSleep [NumOfTimesToEat]");
		return (false);
	}
	if (!get_conditions(ac, av, cond))
		return (false);
	return (true);
}
