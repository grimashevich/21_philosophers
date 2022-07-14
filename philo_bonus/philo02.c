/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:14:09 by EClown            #+#    #+#             */
/*   Updated: 2022/07/14 19:06:59 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	switch_life_state(t_table *table, t_phil *phil);
int		died_of_hunger(t_table *table, t_phil *phil);
void	unlock_dead_sem(t_table *table);
void	*phil_dies(t_table *table, t_phil *phil);

void	take_forks(t_table *table, t_phil *phil)
{
	sem_wait(table->forks_sem);
	phil_say_state(table, phil, 1);
	sem_wait(table->forks_sem);
	phil_say_state(table, phil, 1);
	pthread_mutex_lock(phil->last_eat_time_mutex);
	phil->last_eat_time = get_miliseconds(table->timeval);
	pthread_mutex_unlock(phil->last_eat_time_mutex);
}

void	put_forks_back(t_table *table)
{
	sem_post(table->forks_sem);
	sem_post(table->forks_sem);
}

void	*phil_life(void	*data)
{
	t_transfer	*transfer;
	t_table		*table;
	t_phil		*phil;

	transfer = (t_transfer *)data;
	table = transfer->table;
	phil = transfer->phil;
	while (1)
	{
		take_forks(table, phil);
		switch_life_state(table, phil);
		my_sleep(table, table->time_to_eat);
		put_forks_back(table);
		increase_eat_count(phil, table);
		switch_life_state(table, phil);
		my_sleep(table, table->time_to_sleap);
		switch_life_state(table, phil);
	}
	return (NULL);
}

void	*check_someone_died(void *data)
{
	t_transfer	*transfer;
	t_table		*table;
	t_phil		*phil;

	transfer = (t_transfer *)data;
	phil = transfer->phil;
	table = transfer->table;
	sem_wait(table->someone_died_sem);
	pthread_mutex_lock(phil->someone_died_mutex);
	phil->someone_died = 1;
	pthread_mutex_unlock(phil->someone_died_mutex);
	return (NULL);
}

void	*check_phil_alive(void *data)
{
	t_transfer	*transfer;
	t_table		*table;
	t_phil		*phil;
	long		last_eat_time;

	transfer = (t_transfer *)data;
	table = transfer->table;
	phil = transfer->phil;
	while (1)
	{
		pthread_mutex_lock(phil->last_eat_time_mutex);
		last_eat_time = get_miliseconds(table->timeval) - phil->last_eat_time;
		pthread_mutex_unlock(phil->last_eat_time_mutex);
		if (last_eat_time >= table->time_to_die)
			return (phil_dies(table, phil));
		usleep(500);
	}
	return (NULL);
}
