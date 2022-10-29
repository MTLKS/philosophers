/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:50:04 by maliew            #+#    #+#             */
/*   Updated: 2022/10/29 16:31:37 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_init_fork(t_table *table)
{
	table->forks = sem_open("forks", O_CREAT, 0644, table->philo_amt);
	sem_unlink("forks");
	if (table->forks == NULL)
		philo_exit(table);
}

void	philo_init_philo(t_table *table)
{
	int		i;
	char	*tmp;

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
		tmp = philo_sem_join("m_last_eat", i);
		table->philos[i].m_last_eat = sem_open(tmp, O_CREAT, 0644, 1);
		sem_unlink(tmp);
		free(tmp);
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
	table->m_message = sem_open("m_message", O_CREAT, 0644, 1);
	sem_unlink("m_message");
	table->m_status = sem_open("m_status", O_CREAT, 0644, 1);
	sem_unlink("m_status");
	table->m_philo_done = sem_open("m_philo_done", O_CREAT, 0644, 0);
	sem_unlink("m_philo_done");
	philo_init_fork(table);
	philo_init_philo(table);
	return (table);
}
