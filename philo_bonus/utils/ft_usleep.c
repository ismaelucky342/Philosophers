/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:48:28 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/30 22:48:38 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	ft_usleep(int time_action)
{
	long	start;

	start = ft_current_time();
	while (ft_current_time() < start + time_action)
		usleep(10);
}
