/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:18:15 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/10 19:27:07 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "printing_utils.h"
#include "time_utils.h"
#include "flag_utils.h"
#include <pthread.h>
#include <stdbool.h>

bool	grab_fork(t_philo philo, t_flag fork)
{
	if (pthread_mutex_lock(&philo.printing->mtx) != 0)
		return (false);
	if (pthread_mutex_lock(&fork.mtx) != 0)
		return (false);
	if (!printing(philo, 0, "has taken a fork"))
		return (false);
	if (pthread_mutex_unlock(&philo.printing->mtx) != 0)
		return (false);
	return (true);
}

bool	eat(t_philo philo)
{
	if (pthread_mutex_lock(&philo.lm_flag.mtx) != 0)
		return (false);
	if (pthread_mutex_lock(&philo.printing->mtx) != 0)
		return (false);
	if (!printing(philo, 1, "is eating"))
		return (false);
	if (pthread_mutex_unlock(&philo.printing->mtx) != 0)
		return (false);
	if (pthread_mutex_unlock(&philo.lm_flag.mtx) != 0)
		return (false);
	better_usleep(philo.tt_eat * 1000);
	return (true);
}

bool	philo_sleep(t_philo philo)
{
	if (pthread_mutex_lock(&philo.printing->mtx) != 0)
		return (false);
	if (!printing(philo, 0, "is sleeping"))
		return (false);
	if (pthread_mutex_unlock(&philo.printing->mtx) != 0)
		return (false);
	better_usleep(philo.tt_sleep * 1000);
	return (true);
}

bool	think(t_philo philo)
{
	if (pthread_mutex_lock(&philo.printing->mtx) != 0)
		return (false);
	if (!printing(philo, 0, "is thinking"))
		return (false);
	if (pthread_mutex_unlock(&philo.printing->mtx) != 0)
		return (false);
	return (true);
}

bool	die(t_philo philo)
{
	if (pthread_mutex_lock(&philo.has_died->mtx) != 0)
		return (false);
	if (pthread_mutex_lock(&philo.printing->mtx) != 0)
		return (false);
	if (!philo.has_died->flag)
	{
		printf("\033[0;9%cm %llu %d died\n", (philo.id % 7) + 1 + '0', \
			(get_time() - *philo.start_time) / 1000, philo.id);
		philo.has_died->flag = 1;
	}
	if (pthread_mutex_unlock(&philo.printing->mtx) != 0)
		return (false);
	if (pthread_mutex_unlock(&philo.has_died->mtx) != 0)
		return (false);
	return (true);
}