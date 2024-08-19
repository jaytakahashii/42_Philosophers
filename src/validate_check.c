/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:00:36 by jtakahas          #+#    #+#             */
/*   Updated: 2024/08/19 19:22:28 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	validate_check(int ac, char **av, t_data *data)
{
	int (index) = 0;
	if (ac != 5 && ac != 6)
	{
		error_message("Invalid number of arguments",
			"\nArgs: Philo TimeToDie TimeToEat TimeToSleep [NumOfTimesToEat]");
		return (false);
	}
	while (index + 1 < ac)
	{
		if (!unsigned_long_atoi(av[index + 1], &data->args[index]))
			return (false);
		index++;
	}
	return (true);
}
