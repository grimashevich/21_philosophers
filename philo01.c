/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:25:20 by EClown            #+#    #+#             */
/*   Updated: 2022/06/22 14:52:20 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_phil	*create_phil(void)
{
	t_phil		*phil;
	static int	id = 1;

	phil = malloc(sizeof(t_phil));
	if (! phil)
		return (NULL);
	phil->id = id++;
	phil->state = THINKING;
	phil->next = NULL;
	phil->prev = NULL;
	phil->l_fork = NULL;
	pthread_mutex_init(phil->r_fork, NULL);
	return (phil);
}

void	add_phil_to_table(t_phil *first_phil, t_phil *new_phil)
{
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
	//TODO Останавился тут
}