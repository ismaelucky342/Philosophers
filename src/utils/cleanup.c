/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:27:38 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:27:45 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_lib.h"

static void	destroy_mutexes(t_mutex mutex, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&mutex.mutex_fork[i++]);
	i = 0;
	while (i < n)
		pthread_mutex_destroy(&mutex.mextra[i++]);
}

static int	clean_up_memory(pthread_t *th, t_philosophers *info, t_mutex mutex)
{
	if (info)
	{
		if (info->dead)
			free(info->dead);
		if (info->number_of_meals)
			free(info->number_of_meals);
	}
	free(th);
	free(info);
	if (mutex.mutex_fork)
		free(mutex.mutex_fork);
	if (mutex.mextra)
		free(mutex.mextra);
	return (0);
}

int	clean_up(pthread_t *th, t_philosophers *info, t_mutex mutex, int n)
{
	destroy_mutexes(mutex, n);
	return clean_up_memory(th, info, mutex);
}
