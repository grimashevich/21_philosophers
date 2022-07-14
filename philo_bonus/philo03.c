/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo03.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:32:27 by EClown            #+#    #+#             */
/*   Updated: 2022/07/14 19:09:15 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_sod_notepme(t_table *table, t_phil *phil)
{
	(void) table;
	pthread_mutex_lock(phil->someone_died_mutex);
	if (phil->someone_died)
	{
		pthread_mutex_unlock(phil->someone_died_mutex);
		return (1);
	}
	pthread_mutex_unlock(phil->someone_died_mutex);
	pthread_mutex_lock(phil->ate_enough_mutex);
	if (phil->ate_enough)
	{
		pthread_mutex_unlock(phil->ate_enough_mutex);
		return (1);
	}
	pthread_mutex_unlock(phil->ate_enough_mutex);
	return (0);
}

void	detach_phil_threads(t_phil *phil)
{
	pthread_detach(phil->threads[0]);
	pthread_detach(phil->threads[1]);
	pthread_detach(phil->threads[2]);
}

void	increase_eat_count(t_phil *phil, t_table *table)
{
	int	eat_count;

	pthread_mutex_lock(phil->eat_count_mutex);
	eat_count = ++(phil->eat_count);
	pthread_mutex_unlock(phil->eat_count_mutex);
	if (table->notepme < 0)
		return ;
	pthread_mutex_lock(phil->ate_enough_mutex);
	if (eat_count >= table->notepme)
		phil->ate_enough = 1;
	pthread_mutex_unlock(phil->ate_enough_mutex);
}

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

void	*phil_dies(t_table *table, t_phil *phil)
{
	long		cur_time;

	sem_wait(table->print_sem);
	pthread_mutex_lock(phil->state_mutex);
	phil->state = DIED;
	pthread_mutex_unlock(phil->state_mutex);
	unlock_dead_sem(table);
	cur_time = get_miliseconds(table->timeval) - table->start_time;
	printf("%ld %d died\n", cur_time, phil->id);
	return (NULL);
}
