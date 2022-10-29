/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:50:04 by maliew            #+#    #+#             */
/*   Updated: 2022/10/27 11:16:14 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init_fork(t_table *table)
{
	int	i;

	table->forks = (t_fork *)malloc(table->philo_amt * sizeof(t_fork));
	if (table->forks == NULL)
		philo_exit(table);
	i = -1;
	while (++i < table->philo_amt)
		pthread_mutex_init(&table->forks[i].mutex, NULL);
}

void	philo_init_philo(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(table->philo_amt * sizeof(t_philo));
	if (table->philos == NULL)
		philo_exit(table);
	i = -1;
	while (++i < table->philo_amt)
	{
		table->philos[i].table = table;
		table->philos[i].number = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].last_eat = 0;
		table->philos[i].left_fork = &table->forks[i];
		pthread_mutex_init(&table->philos[i].m_last_eat, NULL);
		pthread_mutex_init(&table->philos[i].m_eat_count, NULL);
		if (i != table->philo_amt - 1)
			table->philos[i].right_fork = &table->forks[i + 1];
		else if (table->philo_amt != 1)
			table->philos[i].right_fork = &table->forks[0];
		else
			table->philos[i].right_fork = NULL;
	}
}

t_table	*philo_init(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->philo_amt = ft_atol(argv[1]);
	table->t2die = ft_atol(argv[2]);
	table->t2eat = ft_atol(argv[3]);
	table->t2sleep = ft_atol(argv[4]);
	table->eat_amt = -1;
	if (argc == 6)
		table->eat_amt = ft_atol(argv[5]);
	pthread_mutex_init(&table->m_message, NULL);
	pthread_mutex_init(&table->m_status, NULL);
	philo_init_fork(table);
	philo_init_philo(table);
	return (table);
}
