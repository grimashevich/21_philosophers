/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:25:20 by EClown            #+#    #+#             */
/*   Updated: 2022/06/28 19:43:31 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_phil	*create_phil(t_table *table)
{
	t_phil		*phil;
	static int	id = 1;

	phil = malloc(sizeof(t_phil));
	if (! phil)
		return (NULL);
	phil->r_fork = malloc(sizeof(t_mutex));
	if (! phil->r_fork)
	{
		free(phil);
		return (NULL);
	}
	phil->id = id++;
	phil->thread_id = 0;
	phil->state = THINKING;
	phil->next = NULL;
	phil->prev = NULL;
	pthread_mutex_init(phil->r_fork, NULL);
	phil->l_fork = phil->r_fork;
	phil->eat_count_mutex = malloc(sizeof(t_mutex));
	pthread_mutex_init(phil->eat_count_mutex, NULL);
	phil->eat_count = 0;
	phil->last_eat_time = get_miliseconds(table->timeval);
	return (phil);
}

void	add_phil_to_table(t_phil *first_phil, t_phil *new_phil)
{
	t_phil	*last_phil;

	if (first_phil->next == NULL)
	{
		first_phil->next = new_phil;
		first_phil->prev = new_phil;
		first_phil->l_fork = new_phil->r_fork;
		new_phil->next = first_phil;
		new_phil->prev = first_phil;
		new_phil->l_fork = first_phil->r_fork;
		return;
	}
	last_phil = first_phil->prev;
	new_phil->next = first_phil;
	new_phil->prev = last_phil;
	last_phil->next = new_phil;
	first_phil->prev = new_phil;
	new_phil->l_fork = last_phil->r_fork;
	first_phil->l_fork = new_phil->r_fork;
}

void	phil_say_state(t_table *table, t_phil *phil, int taking_fork)
{
	long	cur_time;

	pthread_mutex_lock(table->print_mutex);
	cur_time = get_miliseconds(table->timeval) - table->start_time;
	if (taking_fork)
		printf("%ld %d has taken a fork\n", cur_time, phil->id);
	else if (phil->state == EATING)
		printf("%ld %d  is eating\n", cur_time, phil->id);
	else if (phil->state == SLEEPING)
		printf("%ld %d  is sleeping\n", cur_time, phil->id);
	else if (phil->state == THINKING)
		printf("%ld %d  is thinking\n", cur_time, phil->id);
	else if (phil->state == DIED)
		printf("%ld %d  is died\n", cur_time, phil->id);
	pthread_mutex_unlock(table->print_mutex);
}

void	switch_life_state(t_table *table, t_phil *phil)
{
	phil->state = (phil->state + 1) % 3;
	phil_say_state(table, phil, 0);
}

void	increase_eat_count(t_phil *phil)
{
	pthread_mutex_lock(phil->eat_count_mutex);
	phil->eat_count++;
	pthread_mutex_unlock(phil->eat_count_mutex);
}