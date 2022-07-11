/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:25:20 by EClown            #+#    #+#             */
/*   Updated: 2022/07/11 17:46:29 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	phil_life(t_table *table, t_phil *phil);

typedef struct s_phil_ckecklist
{
	int	someone_die;
	int	notepme;
}	t_phil_checklist;


void	phil_main(t_table *table, t_phil *phil)
{
	t_phil_checklist	check_list;
	t_transfer			*transfer;
	int					status;
	
	transfer = malloc(sizeof(transfer));
	transfer->phil = phil;
	transfer->table = table;
	
	//TODO philo_life
	pthread_create(&(phil->threads[0]), NULL, phil_life, transfer);
	
	//TODO check is_phil_alive
	pthread_create(&(phil->threads[1]), NULL, check_phil_alive, transfer);
	//TODO check someone_died
	
	while (1)
	{
		if (check_list.someone_die || check_list.notepme)
			break;
	}
}

void	create_phil_mutex(t_phil *phil)
{
	phil->state_mutex = malloc(sizeof(t_mutex));
	pthread_mutex_init(phil->state_mutex, NULL);
	phil->someone_died_mutex = malloc(sizeof(t_mutex));
	pthread_mutex_init(phil->someone_died_mutex, NULL);
	phil->eat_count_mutex = malloc(sizeof(t_mutex));
	pthread_mutex_init(phil->eat_count_mutex, NULL);
	phil->last_eat_time_mutex = malloc(sizeof(t_mutex));
	pthread_mutex_init(phil->last_eat_time_mutex, NULL);
}

t_phil	*create_phil(t_table *table, int id)
{
	t_phil		*phil;

	phil = malloc(sizeof(t_phil));
	if (! phil)
		return (NULL);
	phil->id = id;
	phil->someone_died = 0;

	phil->state = THINKING;
	phil->eat_count = 0;
	phil->last_eat_time = get_miliseconds(table->timeval);
	phil->threads = malloc(sizeof(pthread_t *) * 4);
	phil->threads[3] = NULL;
	create_phil_mutex(phil);
	return (phil);
}



void	phil_say_state(t_table *table, t_phil *phil, int taking_fork)
{
	long	cur_time;

	sem_wait(table->print_sem);
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
	sem_post(table->print_sem);
}

void	switch_life_state(t_table *table, t_phil *phil)
{
	pthread_mutex_lock(phil->state_mutex);
	phil->state = (phil->state + 1) % 3;
	pthread_mutex_unlock(phil->state_mutex);
	phil_say_state(table, phil, 0);
}
