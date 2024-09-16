/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:45:43 by jay               #+#    #+#             */
/*   Updated: 2024/09/16 16:59:57 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

/* defining colors for the output */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define COLOR_END "\033[0m"
/* ****************************** */

/* defining the structure for the philosophers */

# define THINKING 2
# define SLEEPING 1
# define EATING 0

typedef struct s_conditions
{
	unsigned long	num_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	num_of_times_to_eat;
}	t_conditions;

typedef struct s_table
{
	int				*state;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	int				num_philosophers;
	t_conditions	conditions;
}	t_table;

typedef struct s_philos
{
	int		id;
	int		global_time;
	t_table	*table;
}	t_philos;

/* defining the structure for the allocations */
typedef struct s_allocations
{
	void					*ptr;
	struct s_allocations	*next;
}	t_allocations;

/* function prototypes */
// utils/
void	error_message(char *main_msg, char *sub_msg);
bool	unsigned_long_atoi(char *str, unsigned long *num);
void	pass_space(char **str);

// ft_malloc.c
bool	add_allocations(void *ptr, t_allocations **allocations);
void	free_allocations(t_allocations **allocations);
void	*ft_malloc(size_t size, t_allocations **allocations);

// validate_check.c
bool	validate_check(int ac, char **av, t_conditions *conditions);

void	*philosopher_loop(void *philo);

#endif
