/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:07:47 by EClown            #+#    #+#             */
/*   Updated: 2022/06/23 16:32:08 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 

//FIXME ОСТАНОВИЛСЯ ТУТ
void	*free_table_return_null(void *to_free)
{
	free(to_free);
	return (NULL);
} */

t_table	*table_init(void)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (! table)
		return (NULL);
	table->print_mutex = malloc(sizeof(t_mutex));
	if (! table->print_mutex)
		return (free_and_return_null(table));
	pthread_mutex_init(table->print_mutex, NULL);
	table->someone_die_mutex = malloc(sizeof(t_mutex));
	if (! table->someone_die_mutex)

	table->first_phil = NULL;
	table->someone_die = 0;
}