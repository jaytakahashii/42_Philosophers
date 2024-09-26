/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:45:43 by jay               #+#    #+#             */
/*   Updated: 2024/09/26 19:29:18 by jtakahas         ###   ########.fr       */
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
# include <inttypes.h>

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
	bool			finish;
	pthread_mutex_t	*forks;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	dead_lock;
	struct s_philos	*philos;
}	t_central;

typedef struct s_conditions
{
	uint64_t	num_of_philos;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	uint64_t	must_eat;
}	t_conditions;

typedef struct s_philos
{
	pthread_t		thread;
	int				id;
	bool			is_eating;
	uint64_t		eat_count;
	t_conditions	*conditions;
	uint64_t		start_time;
	uint64_t		last_eat_time;
	bool			*finish;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*time_lock;
	t_central		*central;
}	t_philos;

/* function prototypes */
// utils/
void		error_message(char *main_msg, char *sub_msg);
void		pass_space(char **str);
void		log_event(t_central *central, int id, const char *event);
uint64_t	get_time_in_ms(void);
void		ft_usleep(uint64_t time);

// uint64_atoi.c
bool		is_uint_atoi(char *str, uint64_t *num);

// validate_check.c
bool		validate_and_get_conditions(int ac, char **av,
				t_conditions *conditions);

void		*lifecycle(void *arg);

// initialize.c
bool		init_central(t_central *central, t_philos *philos,
				t_conditions conditions);
bool		init_philos(t_central *central, t_philos *philos,
				t_conditions *conditions);
void		conditions_init(t_conditions *conditions);

// observers.c
void		*program_observer(void *arg);
bool		dead_check(t_philos *philo);

#endif
