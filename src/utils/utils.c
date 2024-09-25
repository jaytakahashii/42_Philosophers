/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:59:48 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/25 19:00:14 by jtakahas         ###   ########.fr       */
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

int	ft_usleep(__uint64_t time)
{
	__uint64_t	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < time)
	{
		// printf("usleep\n");
		usleep(100);
	}
	return (0);
}

__uint64_t	get_time_in_ms(void)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_message("gettimeofday() failed", NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	log_event(t_data *data, int id, const char *event)
{
	__uint64_t	timestamp;

	pthread_mutex_lock(&data->time_lock);
	timestamp = get_time_in_ms() - data->philos[0].start_time;
	pthread_mutex_unlock(&data->time_lock);
	pthread_mutex_lock(&data->print_lock);
	printf("%lu %d %s\n", timestamp, id, event);
	pthread_mutex_unlock(&data->print_lock);
}
