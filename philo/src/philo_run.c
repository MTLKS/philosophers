/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:23:48 by maliew            #+#    #+#             */
/*   Updated: 2022/10/27 08:43:19 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_take_fork(t_philo *philo, t_fork *fork)
{
	int	taken;

	if (fork == NULL)
		return (1);
	taken = 0;
	while (!taken)
	{
		pthread_mutex_lock(&fork->mutex);
		if (fork->philo == 0)
		{
			fork->philo = philo->number;
			taken = 1;
		}
		pthread_mutex_unlock(&fork->mutex);
		if (!taken)
			usleep(500);
	}
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
	philo_eat_count(philo, SET);
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->philo = 0;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->philo = 0;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->number % 2 == 0)
		philo_usleep(1000);
	while (philo_status(philo->table, -1) == 0)
	{
		if (philo_take_fork(philo, philo->left_fork)
			|| philo_take_fork(philo, philo->right_fork)
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

	table->start_time = philo_get_time();
	i = -1;
	while (++i < table->philo_amt)
		pthread_create(&table->philos[i].thread, NULL, &philo_routine,
			&table->philos[i]);
}
