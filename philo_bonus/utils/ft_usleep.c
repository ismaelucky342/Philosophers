/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:15:46 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 02:36:44 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(t_philosophers *philo)
{
	ft_print_message(SLEEPING, philo);
	usleep(philo->data->time_to_sleep * 1000);
}