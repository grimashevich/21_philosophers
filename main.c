/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:05:09 by EClown            #+#    #+#             */
/*   Updated: 2022/06/20 14:48:13 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <string.h>



typedef struct s_philo
{
	t_mutex	mutex;
	int		num;
} t_philo;


void error_exit(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

/*SOME DESCRIPTION*/
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

int main(void)
{
	pthread_t	id;
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
	return (0);
}
