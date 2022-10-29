/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:33:45 by maliew            #+#    #+#             */
/*   Updated: 2022/10/27 11:18:37 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	philo_check_death(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_amt && philo_status(table, -1) == 0)
	{
		if (philo_last_eat(&table->philos[i], GET) + table->t2die
			< philo_get_timestamp(table->start_time))
		{
			philo_status(table, 1);
			printf("%d %d died\n",
				philo_get_timestamp(table->start_time), i + 1);
		}
	}
}

void	philo_check_win(t_table *table)
{
	int	i;
	int	win;

	i = -1;
	win = 1;
	while (++i < table->philo_amt)
	{
		if (table->eat_amt == -1
			|| philo_eat_count(&table->philos[i], GET) < table->eat_amt)
			win = 0;
	}
	if (win == 1)
		philo_status(table, 2);
}

void	philo_check_status(t_table *table)
{
	while (philo_status(table, -1) == 0)
	{
		philo_check_death(table);
		philo_check_win(table);
		usleep(500);
	}
}
