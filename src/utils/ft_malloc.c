/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:16:28 by jtakahas          #+#    #+#             */
/*   Updated: 2024/08/19 17:23:56 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

typedef struct s_allocations
{
	void	*ptr;
	struct s_allocations	*next;
}	t_allocations;

bool	add_allocations(void *ptr, t_allocations **allocations)
{
	t_allocations	*new;

	new = ft_malloc(sizeof(t_allocations), allocations, ptr);
	if (!new)
	{
		free_allocations(allocations);
		return ;
	}
	new->ptr = ptr;
	new->next = *allocations;
	*allocations = new;
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

bool	*ft_malloc(size_t size, t_allocations **allocations, void *ptr)
{
	void	*new;

	new = malloc(size);
	if (!new)
	{
		free_allocations(allocations);
		return (NULL);
	}
	if (!add_allocations(new, allocations))
	{
		free(new);
		return (NULL);
	}
	return (new);
}
