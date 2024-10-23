/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:37:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/23 16:22:17 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_eat(t_global_info *data)
{
	pthread_mutex_lock(data->mutex_l_ate);
	data->last_ate = ft_get_time() - data->start_time;
	pthread_mutex_unlock(data->mutex_l_ate);
	printf(COLOR_GREEN "%lld %d is eating\n" COLOR_RESET, data->last_ate,
		data->philo);
	pthread_mutex_lock(data->mutex_to_eats);
	data->number_eats[data->philo - 1] += 1;
	pthread_mutex_unlock(data->mutex_to_eats);
}

void	ft_print_death(t_global_info *data)
{
	pthread_mutex_lock(data->mutex_to_print);
	printf(COLOR_RED "%lld %d died\n" COLOR_RESET, ft_get_time()
		- data->start_time, data->philo);
	pthread_mutex_unlock(data->mutex_to_print);
}

void	ft_print(t_global_info *data, int action)
{
	pthread_mutex_lock(data->mutex_to_print);
	if (checker_dead(data) == 0)
	{
		if (action == FORK)
			printf(COLOR_YELLOW "%lld %d has taken a fork\n" COLOR_RESET,
				ft_get_time() - data->start_time, data->philo);
		else if (action == EAT)
			print_eat(data);
		else if (action == SLEEP)
			printf(COLOR_BLUE "%lld %d is sleeping\n" COLOR_RESET, ft_get_time()
				- data->start_time, data->philo);
		else if (action == THINK)
			printf(COLOR_CYAN "%lld %d is thinking\n" COLOR_RESET, ft_get_time()
				- data->start_time, data->philo);
	}
	pthread_mutex_unlock(data->mutex_to_print);
}
