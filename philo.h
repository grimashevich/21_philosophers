/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:29:39 by EClown            #+#    #+#             */
/*   Updated: 2022/06/27 18:58:15 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>

# define LLI_MIN "9223372036854775808"
# define LLI_MAX "9223372036854775807"

typedef pthread_mutex_t t_mutex;
typedef struct timeval	t_timeval;

enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_phil
{
	int				id;
	enum e_state	state;
	struct s_phil	*next;
	struct s_phil	*prev;
	t_mutex			*l_fork;
	t_mutex			*r_fork;
	long			last_eat_time;
}	t_phil;

typedef struct s_table
{
	t_phil		*first_phil;
	t_mutex		*print_mutex;
	int			someone_die;
	t_mutex		*someone_die_mutex;
	t_timeval	*timeval;
	long		start_time;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleap;
	int			notepme;
}	t_table;

typedef struct	s_transfer
{
	t_table	*table;
	t_phil	*phil;
}	t_transfer;

t_phil	*create_phil(t_table *table);
void	add_phil_to_table(t_phil *first_phil, t_phil *new_phil);
long	get_miliseconds(t_timeval *timeval);
void	phil_say_state(t_table *table, t_phil *phil, int taking_fork);
void	my_sleep(t_table *table, int miliseconds);

#endif // PHILO_H