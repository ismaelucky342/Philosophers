/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:03:22 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 14:03:36 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	ft_usleep(size_t ms)
{
	size_t	start;

	start = ft_get_time();
	while (ft_get_time() - start < ms)
		usleep(100);
}