/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:29:39 by EClown            #+#    #+#             */
/*   Updated: 2022/06/22 14:11:23 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>

typedef pthread_mutex_t t_mutex;

enum e_state
{
	EATING,
	SLEEPING,
	THINKING
};

typedef struct s_phil
{
	int				id;
	enum e_state	state;
	struct s_phil	*next;
	struct s_phil	*prev;
	t_mutex			*l_fork;
	t_mutex			*r_fork;
} t_phil;

typedef struct s_philos
{
	t_phil	*phil;

} t_philo;



#endif // PHILO_H