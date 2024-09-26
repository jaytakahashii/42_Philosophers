/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:45:43 by jay               #+#    #+#             */
/*   Updated: 2024/09/26 17:00:26 by jtakahas         ###   ########.fr       */
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
# include <time.h>
# include <stdint.h>

/* defining colors for the output */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define COLOR_END "\033[0m"
/* ****************************** */

typedef struct timeval	t_timeval;

/* defining the structure for the philosophers */
typedef struct s_central
{
	bool			dead_flag;
	bool			finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	dead_lock;
	struct s_philos	*philos;
}	t_central;

typedef struct s_conditions
{
	__uint64_t	num_of_philos;
	__uint64_t	time_to_die;
	__uint64_t	time_to_eat;
	__uint64_t	time_to_sleep;
	__uint64_t	must_eat;
}	t_conditions;

typedef struct s_philos
{
	pthread_t		thread;
	int				id;
	bool			is_eating;
	__uint64_t		eat_count;
	t_conditions	*conditions;
	__uint64_t		start_time;
	__uint64_t		last_eat_time;
	bool			*dead;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t *dead_lock;
	pthread_mutex_t	*time_lock;
	t_central			*central;
}	t_philos;

/* defining the structure for the allocations */
typedef struct s_allocations
{
	void					*ptr;
	struct s_allocations	*next;
}	t_allocations;

/* function prototypes */
// utils/
void		error_message(char *main_msg, char *sub_msg);
void		pass_space(char **str);
void		log_event(t_central *central, int id, const char *event);
__uint64_t	get_time_in_ms(void);
int			ft_usleep(__uint64_t time);

// uint64_atoi.c
bool	is_uint_atoi(char *str, __uint64_t *num);
bool	is_atoi(char *str, int *num);

// ft_malloc.c
bool		add_allocations(void *ptr, t_allocations **allocations);
void		free_allocations(t_allocations **allocations);
void		*ft_malloc(size_t size, t_allocations **allocations);

// validate_check.c
bool		validate_and_get_conditions(int ac, char **av, t_conditions *conditions);

void		*lifecycle(void *arg);

// initialize.c
bool		init_data(t_central *central, t_philos *philos, t_conditions conditions);
bool		init_philos(t_central *central, t_philos *philos, t_conditions *conditions);

// observers.c
void	*program_observer(void *arg);


#endif
