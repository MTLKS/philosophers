/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:33:45 by maliew            #+#    #+#             */
/*   Updated: 2022/10/29 15:05:01 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_check(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong argument count.\n");
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if (ft_strisdigit(argv[i]) == 0)
		{
			printf("Error: Argument '%s' is invalid.\n", argv[i]);
			return (1);
		}
		else if (ft_atol(argv[i]) > 2147483647)
		{
			printf("Error: Argument '%s' is too large.\n", argv[i]);
			return (1);
		}
	}
	return (0);
}

int	philo_check_death(t_philo *philo)
{
	int	dead;

	dead = philo_last_eat(philo, GET) + philo->table->t2die
		< philo_get_timestamp(philo->table->start_time);
	return (dead);
}

void	philo_check_win(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_amt)
		sem_wait(table->m_philo_done);
	philo_exit(table);
}

void	philo_check_status(t_table *table)
{
	int	checker_pid;
	int	new_pid;
	int	i;
	int	philo_num;

	checker_pid = fork();
	if (checker_pid == 0)
		philo_check_win(table);
	new_pid = waitpid(-1, NULL, 0);
	i = -1;
	while (++i < table->philo_amt)
	{
		if (table->philos[i].pid != new_pid)
			kill(table->philos[i].pid, SIGINT);
		else
			philo_num = i + 1;
	}
	if (checker_pid != new_pid)
	{
		kill(checker_pid, SIGINT);
		printf("%d %d died\n",
			philo_get_timestamp(table->start_time), philo_num);
	}
}
