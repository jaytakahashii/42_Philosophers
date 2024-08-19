/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:16:28 by jtakahas          #+#    #+#             */
/*   Updated: 2024/08/19 19:37:46 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	add_allocations(void *ptr, t_allocations **allocations)
{
	t_allocations	*new;

	if (!ft_malloc(sizeof(t_allocations), allocations, &new))
		return (false);
	new->ptr = ptr;
	new->next = *allocations;
	*allocations = new;
	return (true);
}

void	free_allocations(t_allocations **allocations)
{
	t_allocations	*tmp;

	while (*allocations)
	{
		tmp = *allocations;
		*allocations = (*allocations)->next;
		free(tmp->ptr);
		free(tmp);
	}
}

bool	ft_malloc(size_t size, t_allocations **allocations, void *ptr)
{
	ptr = malloc(size);
	if (!ptr)
	{
		free_allocations(allocations);
		return (false);
	}
	if (!add_allocations(ptr, allocations))
	{
		free(ptr);
		return (false);
	}
	return (true);
}
