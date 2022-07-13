/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo03.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:32:27 by EClown            #+#    #+#             */
/*   Updated: 2022/07/13 14:29:54 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_sod_notepme(t_table *table, t_phil *phil)
{
	(void) table;
	pthread_mutex_lock(phil->someone_died_mutex);
	if (phil->someone_died)
	{
				sem_wait(table->print_sem);
				printf("SOMEONE DIED say: PHIL # %d\n", phil->id);
				sem_post(table->print_sem);
		return (1);
	}
	pthread_mutex_unlock(phil->someone_died_mutex);
	pthread_mutex_lock(phil->ate_enough_mutex);
	if (phil->ate_enough)
	{
				sem_wait(table->print_sem);
				printf("ATE ENOUGHT say: PHIL # %d\n", phil->id);
				sem_post(table->print_sem);
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

/* int	died_of_hunger(t_table *table, t_phil *phil)
{
	long	cur_time;

	pthread_mutex_lock(phil->last_eat_time_mutex);
	if (get_miliseconds(table->timeval)
		- phil->last_eat_time > table->time_to_die)
	{
		pthread_mutex_lock(table->print_mutex);
		pthread_mutex_lock(phil->state_mutex);
		phil->state = DIED;
		pthread_mutex_unlock(phil->state_mutex);
		cur_time = get_miliseconds(table->timeval) - table->start_time;
		printf("%ld %d died\n", cur_time, phil->id);
		pthread_mutex_lock(table->someone_die_mutex);
		table->someone_die = 1;
		pthread_mutex_unlock(table->someone_die_mutex);
		pthread_mutex_unlock(phil->last_eat_time_mutex);
		return (1);
	}
	pthread_mutex_unlock(phil->last_eat_time_mutex);
	return (0);
} */

/* Return 1 if all philos eat needed times */
/* int	check_all_eat_well(t_table *table)
{
	int		n;
	t_phil	*phil;

	if (table->notepme == 0)
		return (0);
	n = 1;
	phil = table->first_phil;
	while (n <= table->phils_count)
	{
		pthread_mutex_lock(phil->eat_count_mutex);
		if (table->notepme > phil->eat_count)
		{
			pthread_mutex_unlock(phil->eat_count_mutex);
			return (0);
		}
		pthread_mutex_unlock(phil->eat_count_mutex);
		phil = phil->next;
		n++;
	}
	pthread_mutex_lock(table->print_mutex);
	return (1);
} */


void	increase_eat_count(t_phil *phil, t_table *table)
{
	int	eat_count;

	pthread_mutex_lock(phil->eat_count_mutex);
	eat_count = phil->eat_count++;
	pthread_mutex_unlock(phil->eat_count_mutex);
	if (table->notepme  < 0)
	pthread_mutex_lock(phil->ate_enough_mutex);
	if (eat_count >= table->notepme)
		phil->ate_enough = 1;
	pthread_mutex_unlock(phil->ate_enough_mutex);
}
