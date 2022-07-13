/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:59:11 by EClown            #+#    #+#             */
/*   Updated: 2022/07/13 14:18:04 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_table(t_table *table)
{
	sem_close(table->forks_sem);
	sem_close(table->print_sem);
	free(table->timeval);
	free(table);
	return (0);
}
