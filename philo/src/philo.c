/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:34:21 by maliew            #+#    #+#             */
/*   Updated: 2022/10/26 22:30:17 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_exit(t_table *table)
{
	int	i;

	if (table->forks)
	{
		i = -1;
		while (++i < table->philo_amt)
			pthread_mutex_destroy(&table->forks[i].mutex);
		free(table->forks);
	}
	if (table->philos)
	{
		i = -1;
		while (++i < table->philo_amt)
		{
			pthread_mutex_destroy(&table->philos[i].m_last_eat);
			pthread_mutex_destroy(&table->philos[i].m_eat_count);
		}
		free(table->philos);
	}
	pthread_mutex_destroy(&table->m_message);
	pthread_mutex_destroy(&table->m_status);
	free(table);
	exit(0);
}

void	philo_join(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_amt)
		pthread_join(table->philos[i].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (philo_check(argc, argv))
		return (1);
	table = philo_init(argc, argv);
	philo_run(table);
	philo_check_status(table);
	philo_join(table);
	philo_exit(table);
}
