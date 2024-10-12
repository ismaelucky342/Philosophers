/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:02:08 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:34:20 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_lib.h"

void	ft_eat(t_philosophers *data, int fork_1, int fork_2);
void	ft_sleep(t_philosophers *data);
void	ft_think(t_philosophers *data);
void	order_to_eat(t_philosophers *data, int left_fork, int right_fork);

void	*procedure(void *arg)
{
	t_philosophers	*data;
	int				right_fork;
	int				left_fork;

	data = (t_philosophers *)arg;
	left_fork = data->philosopher;
	right_fork = (left_fork % data->parameters.number_philososphers) + 1;
	if (left_fork % 2 != 0)
		ft_usleep(50, data);
	while (1)
	{
		order_to_eat(data, left_fork, right_fork);
		ft_sleep(data);
		if (data->parameters.number_philososphers == 3)
			ft_think(data);
		else
			ft_print(data, THINK);
		pthread_mutex_lock(data->m_protect_dead);
		if (*data->dead == 1)
		{
			pthread_mutex_unlock(data->m_protect_dead);
			return (NULL);
		}
		pthread_mutex_unlock(data->m_protect_dead);
	}
}

void	ft_eat(t_philosophers *data, int fork_1, int fork_2)
{
	pthread_mutex_lock(&data->fork[fork_1]);
	ft_print(data, FORK);
	pthread_mutex_lock(&data->fork[fork_2]);
	ft_print(data, FORK);
	ft_print(data, EAT);
	ft_usleep(data->parameters.t_eat, data);
	pthread_mutex_unlock(&data->fork[fork_2]);
	pthread_mutex_unlock(&data->fork[fork_1]);
}

void	ft_sleep(t_philosophers *data)
{
	ft_print(data, SLEEP);
	ft_usleep(data->parameters.t_sleep, data);
}

void	ft_think(t_philosophers *data)
{
	long	time;

	time = (data->parameters.t_eat * 2) - data->parameters.t_sleep;
	ft_usleep(time * 0.42, data);
	ft_print(data, THINK);
}

void	order_to_eat(t_philosophers *data, int left_fork, int right_fork)
{
	if (left_fork == data->parameters.number_philososphers)
		ft_eat(data, right_fork - 1, left_fork - 1);
	else
		ft_eat(data, left_fork - 1, right_fork - 1);
}