/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:37:43 by maliew            #+#    #+#             */
/*   Updated: 2022/10/26 21:41:24 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_status(t_table *table, int status)
{
	int	new_status;

	pthread_mutex_lock(&table->m_status);
	if (status != -1)
		table->status = status;
	new_status = table->status;
	pthread_mutex_unlock(&table->m_status);
	return (new_status);
}

int	philo_eat_count(t_philo *philo, int type)
{
	int	ret;

	pthread_mutex_lock(&philo->m_eat_count);
	if (type == SET)
		philo->eat_count++;
	ret = philo->eat_count;
	pthread_mutex_unlock(&philo->m_eat_count);
	return (ret);
}

int	philo_last_eat(t_philo *philo, int type)
{
	int	ret;

	pthread_mutex_lock(&philo->m_last_eat);
	if (type == SET)
		philo->last_eat = philo_get_timestamp(philo->table->start_time);
	ret = philo->last_eat;
	pthread_mutex_unlock(&philo->m_last_eat);
	return (ret);
}

int	philo_print(t_philo *philo, int message)
{
	pthread_mutex_lock(&philo->table->m_message);
	if (philo_status(philo->table, -1) != 0)
	{
		pthread_mutex_unlock(&philo->table->m_message);
		return (1);
	}
	printf("%d ", philo_get_timestamp(philo->table->start_time));
	printf("%d ", philo->number);
	if (message == TAKEN_FORK)
		printf("has taken a fork");
	else if (message == IS_EATING)
		printf("is eating");
	else if (message == IS_SLEEPING)
		printf("is sleeping");
	else if (message == IS_THINKING)
		printf("is thinking");
	printf("\n");
	pthread_mutex_unlock(&philo->table->m_message);
	return (0);
}
