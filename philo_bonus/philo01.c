/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:25:20 by EClown            #+#    #+#             */
/*   Updated: 2022/07/14 19:08:30 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*phil_life(void	*data);
void	*check_phil_alive(void *data);
int		check_sod_notepme(t_table *table, t_phil *phil);
void	detach_phil_threads(t_phil *phil);

void	phil_main(t_table *table, t_phil *phil)
{
	t_transfer			*transfer;

	transfer = malloc(sizeof(transfer));
	transfer->phil = phil;
	transfer->table = table;
	if (phil->id % 2 == 0)
		usleep(500);
	pthread_create(&(phil->threads[0]), NULL, phil_life, transfer);
	pthread_create(&(phil->threads[1]), NULL, check_phil_alive, transfer);
	pthread_create(&(phil->threads[2]), NULL, check_someone_died, transfer);
	while (1)
	{
		if (check_sod_notepme(table, phil))
		{
			detach_phil_threads(phil);
			break ;
		}
		usleep(500);
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
	phil->ate_enough_mutex = malloc(sizeof(t_mutex));
	pthread_mutex_init(phil->ate_enough_mutex, NULL);
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
	phil->ate_enough = 0;
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
