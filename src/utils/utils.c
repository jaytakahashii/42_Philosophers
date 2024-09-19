/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:59:48 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/19 19:46:40 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_message(char *main_msg, char *sub_msg)
{
	printf(RED"Error: %s"COLOR_END, main_msg);
	if (sub_msg)
		printf("%s", sub_msg);
	printf("\n");
}

void	pass_space(char **str)
{
	if (!str || !*str)
		return ;
	while (**str && (**str == ' ' || (9 <= **str && **str <= 13)))
		(*str)++;
}

unsigned long	get_time_in_ms(void)
{
	timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	log_event(t_data *data, int id, const char *event)
{
	unsigned long	timestamp;

	timestamp = get_time_in_ms() - data->start_time;
	pthread_mutex_lock(&data->print_lock);
	printf("%lu %d %s\n", timestamp, id, event);
	pthread_mutex_unlock(&data->print_lock);
}