/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:05:09 by EClown            #+#    #+#             */
/*   Updated: 2022/07/05 15:00:50 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

t_table *table_init(int argc, char **argv);
void	*launch_phil(void *data);
void	check_filo_status(t_table *table);

/* typedef struct s_philo
{
	t_mutex	mutex;
	int		num;
} t_philo;


void error_exit(char *msg)
{
	printf("%s\n", msg);
	exit(1);
} */

/*SOME DESCRIPTION*/
/*
void	*hello_thread(void *data)
{
 	char *result;
	
	t_philo	*ph1 = data;
	result = strdup("+++Result from hello thread+++");
	printf("Hello from thread!\n");
	//pthread_mutex_lock(&ph1->mutex);
	while (ph1->num < 100000 && ph1->num > -100000)
	{
		printf("lol: %d\n", ph1->num);
		usleep(200);
		// ph1->num++;
		// ph1->num++;
		// ph1->num++;
		// ph1->num++;
		//pthread_mutex_unlock(&ph1->mutex);
		//pthread_mutex_lock(&ph1->mutex);
	}
	// printf("kek\n");
	//pthread_mutex_unlock(&ph1->mutex);
	return result; 
}
*/

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
		status = pthread_create(&(phil->thread_id), NULL, launch_phil, transfer);
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

int main(int argc, char **argv)
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
	
/* 	pthread_t	id;
	int			status;
	t_philo		*ph1;

	ph1 = calloc(1, sizeof(t_philo));
	pthread_mutex_init(&(ph1->mutex), NULL);
	status = pthread_create(&id, NULL, hello_thread, ph1);
	if (status != 0)
		error_exit("Error creating thread");
	
	// pthread_mutex_lock(&ph1->mutex);

	while (1)
	{
			usleep(200);
		printf("main: %d\n", ph1->num);
		ph1->num--;
		//pthread_mutex_unlock(&ph1->mutex);
		//pthread_mutex_lock(&ph1->mutex);
	}
	//pthread_mutex_unlock(&ph1->mutex);
	status = pthread_join(id, NULL);
	return (0); */
}
