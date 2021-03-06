/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:54 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/25 13:35:17 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	join(t_philo *threads)
{
	int	i;

	i = 0;
	while (threads[i].thread)
	{
		if (pthread_join(threads[i].thread, NULL) != 0)
			error_msg("error: pthread: join failed\n");
		i++;
	}
	free(threads);
}

static void	clear_flags(t_table *table)
{
	int	i;

	i = 0;
	clear_forks(table->forks, table->n_philo);
	while (i < table->n_philo)
	{
		if (pthread_mutex_destroy(&table->philos[i].lm_flag.mtx) != 0)
			error_msg("mutex destroy error\n");
		if (pthread_mutex_destroy(&table->philos[i].n_meals.mtx) != 0)
			error_msg("mutex destroy error\n");
		i++;
	}
	if (pthread_mutex_destroy(&table->has_died.mtx) != 0)
		error_msg("mutex destroy error\n");
	if (pthread_mutex_destroy(&table->printing.mtx) != 0)
		error_msg("mutex destroy error\n");
	if (pthread_mutex_destroy(&table->done_eating.mtx) != 0)
		error_msg("mutex destroy error\n");
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_table	table;

	if (argc != 5 && argc != 6)
		return (error_msg("error: input: invalid amount of arguments\n\
Usage: ./philo [number of philosophers] [tt. die] [tt. eat] \
[tt. sleep] opt. [number of meals]\n"));
	input = parsing(argc, argv);
	if (!input.valid)
		return (error_msg("error: input: input not valid integer\n"));
	if (init_table(&table, input) == -1)
		return (error_msg("error: pthread: init failed\n"));
	join(table.philos);
	clear_flags(&table);
}
