/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo04.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:53:29 by EClown            #+#    #+#             */
/*   Updated: 2022/07/13 14:42:06 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_dead_sem(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->phils_count)
	{
		sem_post(table->someone_died_sem);
		i++;
	}
}

void	*check_phil_alive(void *data)
{
	t_transfer	*transfer;
	t_table		*table;
	t_phil		*phil;
	long	cur_time;

	transfer = (t_transfer *)data;
	table = transfer->table;
	phil = transfer->phil;
	while (1)
	{
		if (get_miliseconds(table->timeval) - phil->last_eat_time >= table->time_to_die)
		{
				sem_wait(table->print_sem);
				printf("DIED of HUNGER say: PHIL # %d\n", phil->id);
				sem_post(table->print_sem);
			sem_wait(table->print_sem);
			pthread_mutex_lock(phil->state_mutex);
			phil->state = DIED;
			unlock_dead_sem(table);
			cur_time = get_miliseconds(table->timeval) - table->start_time;
			printf("%ld %d died\n", cur_time, phil->id);
			return (NULL);
		}
		usleep(500);
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
				sem_wait(table->print_sem);
				printf("SEM SOMONEDIED is OPEN say: PHIL # %d\n", phil->id);
				sem_post(table->print_sem);
	pthread_mutex_lock(phil->someone_died_mutex);
	phil->someone_died = 1;
	pthread_mutex_unlock(phil->someone_died_mutex);
	return (NULL);
}
