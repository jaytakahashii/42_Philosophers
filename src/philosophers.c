/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:45:30 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/16 15:47:09 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_loop(void *philo)
{
	t_philos	*philosopher;
	t_table		*table;

	philosopher = (t_philos *)philo;
	table = philosopher->table;
	while (1)
	{
		// philosopher_thinking();
		// philosopher_hungry();
		// philosopher_eating();
	}
	return (NULL);
}