/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:59:48 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/26 19:29:02 by jtakahas         ###   ########.fr       */
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

void	ft_usleep(uint64_t time)
{
	uint64_t	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < time)
		usleep(100);
}

uint64_t	get_time_in_ms(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	log_event(t_central *cent, int id, const char *event)
{
	uint64_t	timestamp;

	pthread_mutex_lock(&cent->time_lock);
	timestamp = get_time_in_ms() - cent->philos[0].start_time;
	pthread_mutex_unlock(&cent->time_lock);
	pthread_mutex_lock(&cent->print_lock);
	printf("%" PRIu64 " %d %s\n", timestamp, id, event);
	pthread_mutex_unlock(&cent->print_lock);
}
