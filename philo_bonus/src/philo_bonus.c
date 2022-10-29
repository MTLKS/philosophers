/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:34:21 by maliew            #+#    #+#             */
/*   Updated: 2022/10/29 12:54:37 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_exit(t_table *table)
{
	sem_close(table->forks);
	if (table->philos)
		free(table->philos);
	sem_close(table->m_message);
	sem_close(table->m_status);
	free(table);
	exit(0);
}

void	philo_join(void)
{
	while (waitpid(-1, NULL, 0) != -1)
		;
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (philo_check(argc, argv))
		return (1);
	table = philo_init(argc, argv);
	philo_run(table);
	philo_check_status(table);
	philo_join();
	philo_exit(table);
}
