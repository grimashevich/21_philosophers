/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:25:20 by EClown            #+#    #+#             */
/*   Updated: 2022/07/08 19:33:49 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_phil_ckecklist
{
	int	someone_die;
	int	notepme;
}	t_phil_checklist;


void	phil_main(t_table *table, t_phil *phil)
{
	t_phil_checklist	check_list;
	
	//TODO philo_life
	//TODO check is_phil_alive
	//TODO check someone_died
	
	while (1)
	{
		if (check_list.someone_die || check_list.notepme)
			break;
	}
}

t_phil	*create_phil(t_table *table)
{
	t_phil		*phil;
	static int	id = 1;

	phil = malloc(sizeof(t_phil));
	if (! phil)
		return (NULL);
	phil->id = id++;
	phil->thread_id = 0;
	phil->state = THINKING;
	phil->next = NULL;
	phil->prev = NULL;
	create_phil_mutex(phil);
	phil->l_fork = phil->r_fork;
	phil->eat_count = 0;
	phil->last_eat_time = get_miliseconds(table->timeval);
	return (phil);
}



void	phil_say_state(t_table *table, t_phil *phil, int taking_fork)
{
	long	cur_time;

	pthread_mutex_lock(table->print_mutex);
	pthread_mutex_lock(phil->state_mutex);
	cur_time = get_miliseconds(table->timeval) - table->start_time;
	if (taking_fork)
		printf("%ld %d has taken a fork\n", cur_time, phil->id);
	else if (phil->state == EATING)
		printf("%ld %d is eating\n", cur_time, phil->id);
	else if (phil->state == SLEEPING)
		printf("%ld %d is sleeping\n", cur_time, phil->id);
	else if (phil->state == THINKING)
		printf("%ld %d is thinking\n", cur_time, phil->id);
	else if (phil->state == DIED)
	{
		printf("%ld %d died\n", cur_time, phil->id);
		pthread_mutex_unlock(phil->state_mutex);
		return ;
	}
	pthread_mutex_unlock(phil->state_mutex);
	pthread_mutex_unlock(table->print_mutex);
}

void	switch_life_state(t_table *table, t_phil *phil)
{
	pthread_mutex_lock(phil->state_mutex);
	phil->state = (phil->state + 1) % 3;
	pthread_mutex_unlock(phil->state_mutex);
	phil_say_state(table, phil, 0);
}
