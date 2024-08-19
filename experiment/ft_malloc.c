/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:16:28 by jtakahas          #+#    #+#             */
/*   Updated: 2024/08/19 20:15:47 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_allocations
{
	void				*ptr;
	struct s_allocations	*next;
}	t_allocations;

void	free_allocations(t_allocations **allocations);
void	*malloc(size_t size);
void	*ft_malloc(size_t size, t_allocations **allocations);
void	error_message(char *message, char *usage);

void	error_message(char *message, char *usage)
{
	printf("Error: %s\n", message);
	if (usage)
		printf("Usage: %s\n", usage);
	exit(1);
}

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
	*allocations = NULL;
}

void	*ft_malloc(size_t size, t_allocations **allocations)
{
	void	*ptr;

	ptr = malloc(size);
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

// test

int	main(void)
{
	t_allocations	*allocations;
	int				*ptr;
	char			*str;
	char			**strs;

	allocations = NULL;
	ptr = ft_malloc(sizeof(int), &allocations);
	if (ptr == NULL)
		return (1);
	ptr[0] = 42;
	printf("ptr[0]: %d\n", ptr[0]);
	str = ft_malloc(10, &allocations);
	if (str == NULL)
		return (1);
	str[0] = 'H';
	str[1] = 'e';
	str[2] = 'l';
	str[3] = 'l';
	str[4] = 'o';
	str[5] = '\0';
	printf("str: %s\n", str);

	strs = ft_malloc(3 * sizeof(char *), &allocations);
	if (strs == NULL)
		return (1);
	strs[0] = str;
	strs[1] = str + 1;
	strs[2] = str + 2;
	printf("strs[0]: %s\n", strs[0]);
	printf("strs[1]: %s\n", strs[1]);
	printf("strs[2]: %s\n", strs[2]);
	free_allocations(&allocations);
	return (0);
}

void	*malloc(size_t size)
{
	static int	count;

	if (count >= 2)
		return (NULL);
	count++;
	return (calloc(size, 1));
}
