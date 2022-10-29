/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:37:43 by maliew            #+#    #+#             */
/*   Updated: 2022/10/29 12:52:41 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_status(t_table *table, int status)
{
	int	new_status;

	sem_wait(table->m_status);
	if (status != -1)
		table->status = status;
	new_status = table->status;
	sem_post(table->m_status);
	return (new_status);
}

int	philo_last_eat(t_philo *philo, int type)
{
	int	ret;

	if (type == SET)
		philo->last_eat = philo_get_timestamp(philo->table->start_time);
	ret = philo->last_eat;
	return (ret);
}

int	philo_print(t_philo *philo, int message)
{
	sem_wait(philo->table->m_message);
	if (philo_check_death(philo) != 0)
	{
		sem_post(philo->table->m_message);
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
	sem_post(philo->table->m_message);
	return (0);
}
