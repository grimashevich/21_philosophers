/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:05:09 by EClown            #+#    #+#             */
/*   Updated: 2022/07/14 18:40:39 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

t_table	*table_init(int argc, char **argv);
void	check_filo_status(t_table *table);
int		free_table(t_table *table);
void	phil_main(t_table *table, t_phil *phil);

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
	if (ft_atoi(argv[1]) <= 0)
		return (0);
	if (ft_atoi(argv[2]) < 0)
		return (0);
	if (ft_atoi(argv[3]) < 0)
		return (0);
	if (ft_atoi(argv[4]) < 0)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		return (0);
	return (1);
}

int	launch_phil(t_table *table)
{
	int			i;
	pid_t		cur_pid;

	i = 1;
	while (i <= table->phils_count)
	{
		cur_pid = fork();
		if (cur_pid == 0)
		{
			phil_main(table, create_phil(table, i));
			return (1);
		}
		i++;
	}
	return (0);
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
	if (table->notepme == 0)
		return (free_table(table));
	if (launch_phil(table) == 1)
		return (0);
	while (table->phils_count)
	{
		wait(NULL);
		table->phils_count--;
	}
	sem_unlink(SEM_FORKS_NAME);
	sem_unlink(SEM_PRINT_NAME);
	sem_unlink(SEM_SOD_NAME);
	return (0);
}
