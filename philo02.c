/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:14:09 by EClown            #+#    #+#             */
/*   Updated: 2022/06/28 19:45:30 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	switch_life_state(t_table *table, t_phil *phil);
void	increase_eat_count(t_phil *phil);
int		died_of_hunger(t_table *table, t_phil *phil);

void	take_forks(t_table *table, t_phil *phil)
{
	if (phil->id == table->phils_count)
	{
		pthread_mutex_lock(phil->l_fork);
		phil_say_state(table, phil, 1);
		pthread_mutex_lock(phil->r_fork);
		phil_say_state(table, phil, 1);
	}
	else
	{
		pthread_mutex_lock(phil->r_fork);
		phil_say_state(table, phil, 1);
		pthread_mutex_lock(phil->l_fork);
		phil_say_state(table, phil, 1);
	}
}

void	put_forks_back(t_table *table, t_phil *phil)
{
	if (phil->id > phil->next->id)
	{
		pthread_mutex_unlock(phil->r_fork);
		pthread_mutex_unlock(phil->l_fork);
	}
	else
	{
		pthread_mutex_unlock(phil->l_fork);
		pthread_mutex_unlock(phil->r_fork);
	}
	phil->last_eat_time = get_miliseconds(table->timeval);
}

void	phil_dies(t_table *table, t_phil *phil)
{
	phil->state = DIED;
	phil_say_state(table, phil, 0);
	pthread_mutex_lock(table->someone_die_mutex);
	table->someone_die = 1;
	pthread_mutex_unlock(table->someone_die_mutex);
}

void	phil_life(t_table *table, t_phil *phil)
{
	if (phil->id % 2 == 0)
		my_sleep(table, 100);
	while (1)
	{
		take_forks(table, phil);
		if (died_of_hunger(table, phil))
			break;
		switch_life_state(table, phil);
		my_sleep(table, table->time_to_eat);
		put_forks_back(table, phil);
		increase_eat_count(phil);
		switch_life_state(table, phil);
		my_sleep(table, table->time_to_sleap);
		switch_life_state(table, phil);
		if (check_someone_died(table))
			return ;
	}
}

void	*launch_phil(void *data)
{
	t_transfer	*transfer;

	transfer = (t_transfer	*)data;
	phil_life(transfer->table, transfer->phil);
	free(data);
	return (NULL);
}
