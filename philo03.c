/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo03.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:32:27 by EClown            #+#    #+#             */
/*   Updated: 2022/06/28 18:16:46 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	phil_dies(t_table *table, t_phil *phil);

int	died_of_hunger(t_table *table, t_phil *phil)
{
	if (get_miliseconds(table->timeval) - phil->last_eat_time > table->time_to_die)
	{
		phil_dies(table, phil);
		return (1);
	}
	return (0);
}

int	check_someone_died(t_table *table)
{
	int	result;

	pthread_mutex_lock(table->someone_die_mutex);
	result = table->someone_die;
	pthread_mutex_unlock(table->someone_die_mutex);
	return (result);
}

/* Return 1 if all philos eat needed times */
int check_all_eat_well(t_table *table)
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
	}
	return (1);
}

void	check_filo_status(t_table *table)
{
	check_someone_died(table);
	check_all_eat_well(table);
	usleep(500);
}
