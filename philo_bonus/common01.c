/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:07:47 by EClown            #+#    #+#             */
/*   Updated: 2022/07/07 15:03:43 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_table_return_null(void *to_free1, void *to_free2)
{
	if (to_free1)
		free(to_free1);
	if (to_free2)
		free(to_free2);
	return (NULL);
}

long	get_miliseconds(t_timeval *timeval)
{
	gettimeofday(timeval, NULL);
	return (timeval->tv_sec * 1000 + timeval->tv_usec / 1000);
}

t_table	*table_init2(int argc, char **argv, t_table *table)
{
	table->phils_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleap = ft_atoi(argv[4]);
	table->notepme = -1;
	if (argc >= 6)
		table->notepme = ft_atoi(argv[5]);
	return (table);
}

t_table	*table_init(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (! table)
		return (NULL);
	table->print_mutex = malloc(sizeof(t_mutex));
	if (! table->print_mutex)
		return (free_table_return_null(table, NULL));
	pthread_mutex_init(table->print_mutex, NULL);
	table->someone_die_mutex = malloc(sizeof(t_mutex));
	if (! table->someone_die_mutex)
		return (free_table_return_null(table->print_mutex, table));
	pthread_mutex_init(table->someone_die_mutex, NULL);
	table->timeval = malloc(sizeof(t_timeval));
	if (! table->timeval)
	{
		free(table->someone_die_mutex);
		return (free_table_return_null(table->print_mutex, table));
	}
	table->first_phil = NULL;
	table->someone_die = 0;
	table->start_time = get_miliseconds(table->timeval);
	return (table_init2(argc, argv, table));
}

/* sleep in miliseconds */
void	my_sleep(t_table *table, int miliseconds)
{
	long	start;

	start = get_miliseconds(table->timeval);
	while (get_miliseconds(table->timeval) - start < miliseconds)
	{
		usleep(100);
	}
}
