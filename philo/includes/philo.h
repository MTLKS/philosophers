/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:31:22 by maliew            #+#    #+#             */
/*   Updated: 2022/10/26 21:25:17 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define TAKEN_FORK		0
# define IS_EATING		1
# define IS_SLEEPING	2
# define IS_THINKING	3
# define HAS_DIED		4

# define GET 0
# define SET 1

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				philo;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				number;
	int				eat_count;
	int				last_eat;
	pthread_mutex_t	m_eat_count;
	pthread_mutex_t	m_last_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				status;
	int				philo_amt;
	int				t2die;
	int				t2eat;
	int				t2sleep;
	int				eat_amt;
	long			start_time;
	t_fork			*forks;
	struct s_philo	*philos;
	pthread_mutex_t	m_status;
	pthread_mutex_t	m_message;
}	t_table;

// philo.c

void	philo_exit(t_table *table);

// philo_check.c

int		philo_check(int argc, char **argv);
void	philo_check_status(t_table *table);
void	philo_check_win(t_table *table);

// philo_init.c

t_table	*philo_init(int argc, char **argv);

// philo_utils.c

int		ft_strisdigit(char *str);
long	ft_atol(const char *str);
long	philo_get_time(void);
int		philo_get_timestamp(long start_time);
void	philo_usleep(int time);

// philo_utils2.c

int		philo_status(t_table *table, int status);
int		philo_eat_count(t_philo *philo, int type);
int		philo_last_eat(t_philo *philo, int type);
int		philo_print(t_philo *philo, int message);

// philo_run.c

void	*philo_routine(void *arg);
void	philo_run(t_table *table);

#endif