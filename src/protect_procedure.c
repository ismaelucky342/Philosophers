/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_procedure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:02:08 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:20:59 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_lib.h"

int	protect_eat(t_philosophers *data)
{
	int	i;

	i = 0;
	if (data->parameters.meals == 0)
		return (0);
	pthread_mutex_lock(data->m_protect_eat);
	while (i < data->parameters.number_philososphers)
	{
		if (data->number_of_meals[i] < data->parameters.meals)
		{
			pthread_mutex_unlock(data->m_protect_eat);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(data->m_protect_eat);
	pthread_mutex_lock(data->m_protect_dead);
	*data->dead = 1;
	pthread_mutex_unlock(data->m_protect_dead);
	return (1);
}

int	protect_dead(t_philosophers *data)
{
	pthread_mutex_lock(data->m_protect_dead);
	if (*data->dead == 1)
	{
		pthread_mutex_unlock(data->m_protect_dead);
		return (1);
	}
	pthread_mutex_lock(data->m_protect_last_eat);
	if (gettime_ms() - data->init_time
		- data->last_meal > data->parameters.t_die)
	{
		*data->dead = 1;
		pthread_mutex_unlock(data->m_protect_last_eat);
		pthread_mutex_unlock(data->m_protect_dead);
		ft_print_death(data);
		return (1);
	}
	pthread_mutex_unlock(data->m_protect_last_eat);
	pthread_mutex_unlock(data->m_protect_dead);
	return (0);
}

void	*routine_monitor(void *arg)
{
	int				i;
	t_philosophers	*data;

	data = arg;
	while (1)
	{
		i = 0;
		while (i < data->parameters.number_philososphers)
		{
			if (protect_dead(&data[i]) || protect_eat(&data[i]))
				return (NULL);
			i++;
		}
	}
}
