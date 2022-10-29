/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:37:43 by maliew            #+#    #+#             */
/*   Updated: 2022/10/29 16:32:17 by maliew           ###   ########.fr       */
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

	sem_wait(philo->m_last_eat);
	if (type == SET)
		philo->last_eat = philo_get_timestamp(philo->table->start_time);
	ret = philo->last_eat;
	sem_post(philo->m_last_eat);
	return (ret);
}

int	philo_print(t_philo *philo, int message)
{
	sem_wait(philo->table->m_message);
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

char	*philo_sem_join(char *str, int num)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i])
		i++;
	ret = malloc((i + 4) * sizeof(char));
	i = -1;
	while (str[++i])
		ret[i] = str[i];
	ret[i] = (num / 100) + '0';
	ret[++i] = (num / 10 % 10) + '0';
	ret[++i] = (num % 10) + '0';
	ret[++i] = 0;
	return (ret);
}
