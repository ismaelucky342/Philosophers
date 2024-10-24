/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:21:47 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/24 23:58:01 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	check_wait(t_philosophers *philo, int time)
{
	long long	i;

	i = timestamp();
	while (Hitman(philo))
	{
		if ((-i + timestamp()) >= time)
			break ;
		usleep(100);
	}
	return ;
}