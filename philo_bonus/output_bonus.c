/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:12:35 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/04 00:16:32 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_print(t_philosophers *philo, char *str)
{
	sem_wait(philo->block_printf);
	if (!philo->stop)
		printf("%lld %d %s\n", ft_get_time() - philo->t_start, philo->index, str);
	sem_post(philo->block_printf);
}
