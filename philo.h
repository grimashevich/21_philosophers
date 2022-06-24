/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:29:39 by EClown            #+#    #+#             */
/*   Updated: 2022/06/24 19:54:56 by EClown           ###   ########.fr       */
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
}	t_phil;

typedef struct s_table
{
	t_phil		*first_phil;
	t_mutex		*print_mutex;
	int			someone_die;
	t_mutex		*someone_die_mutex;
	t_timeval	*timeval;
	long	start_time;
}	t_table;

t_phil	*create_phil(void);
void	add_phil_to_table(t_phil *first_phil, t_phil *new_phil);
long	get_miliseconds(t_timeval *timeval);

#endif // PHILO_H