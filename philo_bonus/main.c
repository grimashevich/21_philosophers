/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:05:09 by EClown            #+#    #+#             */
/*   Updated: 2022/07/11 15:59:38 by EClown           ###   ########.fr       */
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


/*
Try to create threads
Return 1 of some error occured, 0 if all ok
*/
/* int	create_threads(t_table *table)
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
} */


int	launch_phil(t_table *table)
{
	int			i;
	pid_t		cur_pid;
	t_phil		*phil;

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
	if (launch_phil == 1)
		return (0);
	
	sem_unlink(SEM_FORKS_NAME);
	sem_unlink(SEM_PRINT_NAME);
	return (0);
}

/* 
void forks_work(int fork_id, sem_t *sem, sem_t *sem_print)
{
	int	i = 3;

	while (i > 0)
	{
		sem_wait(sem);
		sem_wait(sem_print);
		printf("I am fork № %d\n", fork_id);
		sem_post(sem_print);
		usleep(500000);
		sem_post(sem);
		usleep(500000);
		if (i == 3 && fork_id == 3)
		{
			printf("KILL THEM ALL\n");
			sem_wait(sem_print);
			kill(0, SIGTERM);
		}
		i--;
	}
	
}

#define FORKS 7

int main(void)
{
	sem_t	*sem1;
	sem_t	*sem_print;
	int		i;
	int		forks[FORKS];

	sem_unlink("sem_first");
	sem_unlink("sem_print");
	sem1 = sem_open("sem_first", O_CREAT, 0777, 2);
	sem_print = sem_open("sem_print", O_CREAT, 0777, 1);
	i = 0;

	while (i < FORKS)
	{
		forks[i] = fork();
		if (forks[i] == 0)
		{
			forks_work(i, sem1, sem_print);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < FORKS)
	{
		wait(NULL);
		i++;
	}
	printf("\nDONE\n");
	
} */