/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:37:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/03 23:59:23 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	ft_usleep(long long time, t_philosophers *philo)
{
	long long	t;

	t = ft_get_time();
	while (!philo->stop)
	{
		if (ft_get_time() - t >= time)
			break ;
		usleep(500);
	}
}
