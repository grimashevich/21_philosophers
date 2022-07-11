/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo04.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:53:29 by EClown            #+#    #+#             */
/*   Updated: 2022/07/11 17:58:36 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_phil_alive(void *data)
{
	t_transfer	*transfer;
	t_table		*table;
	t_phil		*phil;

	transfer = (t_transfer *)data;
	table = transfer->table;
	phil = transfer->phil;

	//TODO останавлился тут. Взять функционал из died_of_hunger(t_table *table, t_phil *phil) //philo03.c, а ее удалить
	
}