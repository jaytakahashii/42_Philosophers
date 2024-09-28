/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:40:06 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/28 13:17:40 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// ULONG_MAX = 18446744073709551615

static bool	negative_check(char **str)
{
	if (!str || !*str)
	{
		error_message("Invalid argument", NULL);
		return (false);
	}
	if (**str == '-')
	{
		error_message("Negative number is not allowed", NULL);
		return (false);
	}
	if (**str == '+')
		(*str)++;
	return (true);
}

static bool	is_ulong(uint64_t num, char str_i)
{
	if (num > LONG_MAX / 10 || (num == LONG_MAX / 10 && str_i >= '6'))
	{
		error_message("Invalid argument", NULL);
		return (false);
	}
	return (true);
}

bool	is_uint_atoi(char *str, uint64_t *num)
{
	if (!str || !*str || !num)
	{
		error_message("Invalid argument", NULL);
		return (false);
	}
	pass_space(&str);
	if (!negative_check(&str))
		return (false);
	while (*str)
	{
		if (*str < '0' || '9' < *str)
		{
			error_message("Invalid argument", NULL);
			return (false);
		}
		*num = *num * 10 + *str - '0';
		if (!is_ulong(*num, *str))
			return (false);
		str++;
	}
	return (true);
}
