/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:07:47 by EClown            #+#    #+#             */
/*   Updated: 2022/07/13 14:44:40 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_miliseconds(t_timeval *timeval)
{
	gettimeofday(timeval, NULL);
	return (timeval->tv_sec * 1000 + timeval->tv_usec / 1000);
}

t_table	*table_init(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (! table)
		return (NULL);
	table->timeval = malloc(sizeof(t_timeval));
	table->start_time = get_miliseconds(table->timeval);
	table->phils_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleap = ft_atoi(argv[4]);
	table->notepme = -1;
	if (argc >= 6)
		table->notepme = ft_atoi(argv[5]);
	return (table);
	table->forks_sem = sem_open(SEM_FORKS_NAME, O_CREAT, 0777, table->phils_count);
	table->print_sem = sem_open(SEM_PRINT_NAME, O_CREAT, 0777, 1);
	table->someone_died_sem = sem_open(SEM_SOD_NAME, O_CREAT, 0777, 0);
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
