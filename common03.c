/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:59:11 by EClown            #+#    #+#             */
/*   Updated: 2022/07/07 14:34:29 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	detouch_threads(t_table *table)
{
	t_phil		*phil;
	int			n;

	phil = table->first_phil;
	n = 0;
	while (n < table->phils_count)
	{
		if (phil->thread_id != 0)
			pthread_detach(phil->thread_id);
		phil = phil->next;
		n++;
	}
}
