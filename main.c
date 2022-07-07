/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:05:09 by EClown            #+#    #+#             */
/*   Updated: 2022/07/07 14:35:24 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

t_table	*table_init(int argc, char **argv);
void	*launch_phil(void *data);
void	check_filo_status(t_table *table);

int	check_args(int argc, char **argv)
{
	if (argc < 5)
		return (0);
	if (argc > 6)
		argc = 6;
	while (argc > 1)
	{
		if (! is_numeric(argv[--argc]))
			return (0);
	}
	return (1);
}

t_phil	*create_philos(t_table *table)
{
	t_phil	*first_phil;
	int		i;

	first_phil = create_phil(table);
	i = 1;
	while (i < table->phils_count)
	{
		add_phil_to_table(first_phil, create_phil(table));
		i++;
	}
	return (first_phil);
}

/*
Try to create threads
Return 1 of some error occured, 0 if all ok
*/
int	create_threads(t_table *table)
{
	t_phil		*phil;
	t_transfer	*transfer;
	int			n;
	int			status;

	phil = table->first_phil;
	n = 1;
	while (n <= table->phils_count)
	{
		transfer = malloc(sizeof(t_transfer));
		transfer->table = table;
		transfer->phil = phil;
		status = pthread_create(&(phil->thread_id), NULL,
				launch_phil, transfer);
		if (status != 0)
			return (1);
		phil = phil->next;
		n++;
	}
	return (0);
}

void	join_threads(t_table *table)
{
	t_phil		*phil;
	int			n;

	phil = table->first_phil;
	n = 1;
	while (n <= table->phils_count)
	{
		if (phil->thread_id != 0)
			pthread_join(phil->thread_id, NULL);
		phil = phil->next;
		n++;
	}
}

int	main(int argc, char **argv)
{
	t_table		*table;

	if (check_args(argc, argv) == 0)
	{
		printf("Bad arguments\n");
		return (1);
	}
	table = table_init(argc, argv);
	table->first_phil = create_philos(table);
	if (create_threads(table) == 0)
	{
		check_filo_status(table);
	}
	detouch_threads(table);
	return (0);
}
