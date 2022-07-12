/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:29:39 by EClown            #+#    #+#             */
/*   Updated: 2022/07/12 16:53:26 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define LLI_MIN "9223372036854775808"
# define LLI_MAX "9223372036854775807"
# define SEM_FORKS_NAME "sem_forks"
# define SEM_PRINT_NAME "sem_print"
# define SEM_SOD_NAME "sem_someone_die"

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_phil
{
	int				id;
	enum e_state	state;
	int				someone_died;
	long			last_eat_time;
	int				eat_count;
	int				ate_enough;
	t_mutex			*state_mutex;
	t_mutex			*someone_died_mutex;
	t_mutex			*last_eat_time_mutex;
	t_mutex			*eat_count_mutex;
	t_mutex			*ate_enough_mutex;
	pthread_t		*threads;
}	t_phil;

typedef struct s_table
{
	sem_t		*print_sem;
	sem_t		*forks_sem;
	sem_t		*someone_died_sem;
	t_timeval	*timeval;
	long		start_time;
	int			phils_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleap;
	int			notepme;
}	t_table;

typedef struct s_transfer
{
	t_table	*table;
	t_phil	*phil;
}	t_transfer;

int		is_numeric(char *str);
int		ft_atoi(const char *str);
t_phil	*create_phil(t_table *table, int id);
void	add_phil_to_table(t_phil *first_phil, t_phil *new_phil);
long	get_miliseconds(t_timeval *timeval);
void	phil_say_state(t_table *table, t_phil *phil, int taking_fork);
void	my_sleep(t_table *table, int miliseconds);
void	*check_someone_died(void *data);
void	increase_eat_count(t_phil *phil, t_table *table);

#endif // PHILO_H	