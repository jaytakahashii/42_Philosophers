/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:16:28 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/25 16:10:18 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	add_allocations(void *ptr, t_allocations **allocations)
{
	t_allocations	*new;

	new = malloc(sizeof(t_allocations));
	if (new == NULL)
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

void	*ft_malloc(size_t size, t_allocations **allocations)
{
	void	*ptr;

	printf("ft_malloc: %zu\n", size);
	ptr = malloc(size);
	printf("ft_malloc: %p\n", ptr);
	if (ptr == NULL)
	{
		free_allocations(allocations);
		error_message("Malloc failed", NULL);
		return (NULL);
	}
	if (!add_allocations(ptr, allocations))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
