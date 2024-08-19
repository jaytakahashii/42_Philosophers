/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:59:48 by jtakahas          #+#    #+#             */
/*   Updated: 2024/08/19 19:12:14 by jtakahas         ###   ########.fr       */
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
