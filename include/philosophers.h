/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:45:43 by jay               #+#    #+#             */
/*   Updated: 2024/08/19 20:26:00 by jtakahas         ###   ########.fr       */
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
typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	struct s_data	*data;
	struct timeval	last_meal;
}	t_philo;

/* defining the structure for the data */
typedef struct s_data
{
	unsigned long	args[6];
	bool			dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
}	t_data;

typedef struct s_allocations
{
	void	*ptr;
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
bool	validate_check(int ac, char **av, t_data *data);


#endif
