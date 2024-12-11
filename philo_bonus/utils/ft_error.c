/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:18:51 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 02:34:04 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_error_msg(t_simulation *simulation, char *message, int ret)
{
	if (simulation)
		if (simulation->forks)
			free(simulation->forks);
	printf("%s\n", message);
	return (ret);
}