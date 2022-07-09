/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:59:11 by EClown            #+#    #+#             */
/*   Updated: 2022/07/07 15:12:54 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_table(t_table *table)
{
	sem_close(SEM_FORKS_NAME);
	sem_close(SEM_PRINT_NAME);
	free(table->timeval);
	free(table);
	return (0);
}
