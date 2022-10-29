/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:23:48 by maliew            #+#    #+#             */
/*   Updated: 2022/10/29 13:47:22 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	philo_take_fork(t_philo *philo)
{
	sem_wait(philo->table->forks);
	if (philo_print(philo, TAKEN_FORK))
		return (1);
	sem_wait(philo->table->forks);
	if (philo_print(philo, TAKEN_FORK))
		return (1);
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	if (philo_print(philo, IS_EATING))
		return (1);
	philo_last_eat(philo, SET);
	philo_usleep(philo->table->t2eat * 1000);
	philo->eat_count++;
	if (philo->eat_count == philo->table->eat_amt)
		sem_post(philo->table->m_philo_done);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	return (0);
}

void	*philo_death_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo_check_death(philo) == 0)
		usleep(500);
	exit(0);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->number % 2 == 0)
		philo_usleep(1000);
	pthread_create(&philo->death_thread, NULL, philo_death_thread, philo);
	pthread_detach(philo->death_thread);
	while (1)
	{
		if (philo_take_fork(philo)
			|| philo_eat(philo)
			|| philo_print(philo, IS_SLEEPING))
			break ;
		philo_usleep(philo->table->t2sleep * 1000);
		if (philo_print(philo, IS_THINKING))
			break ;
		while (philo_get_timestamp(philo->table->start_time)
			< philo->last_eat + philo->table->t2die - 100)
			philo_usleep(500);
	}
	return (NULL);
}

void	philo_run(t_table *table)
{
	int	i;
	int	pid;

	table->start_time = philo_get_time();
	i = -1;
	while (++i < table->philo_amt)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_routine(&table->philos[i]);
			philo_exit(table);
		}
		table->philos[i].pid = pid;
	}
}
