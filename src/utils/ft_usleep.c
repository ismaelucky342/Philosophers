/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:34:42 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:21:35 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_lib.h"

void	ft_usleep(long long wait, t_philosophers *data)
{
	long long	init_time;

	init_time = gettime_ms();
	while (gettime_ms() < init_time + wait)
	{
		if (checker_dead(data) == 1)
			return ;
		usleep(100);
	}
}