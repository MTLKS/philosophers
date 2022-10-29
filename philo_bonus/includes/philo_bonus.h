/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:31:22 by maliew            #+#    #+#             */
/*   Updated: 2022/10/29 16:32:01 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <signal.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>

# define TAKEN_FORK		0
# define IS_EATING		1
# define IS_SLEEPING	2
# define IS_THINKING	3
# define HAS_DIED		4

# define GET 0
# define SET 1

typedef struct s_philo
{
	int				pid;
	int				number;
	int				eat_count;
	int				last_eat;
	sem_t			*m_last_eat;
	pthread_t		death_thread;
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
	sem_t			*forks;
	struct s_philo	*philos;
	sem_t			*m_status;
	sem_t			*m_message;
	sem_t			*m_philo_done;
}	t_table;

// philo.c

void	philo_exit(t_table *table);

// philo_check.c

int		philo_check(int argc, char **argv);
void	philo_check_status(t_table *table);
void	philo_check_win(t_table *table);
int		philo_check_death(t_philo *philo);

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
int		philo_last_eat(t_philo *philo, int type);
int		philo_print(t_philo *philo, int message);
char	*philo_sem_join(char *str, int num);

// philo_run.c

void	*philo_routine(void *arg);
void	philo_run(t_table *table);

#endif