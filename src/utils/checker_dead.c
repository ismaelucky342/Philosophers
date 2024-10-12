/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_dead.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:59:00 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:21:19 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_lib.h"

int	checker_dead(t_philosophers *data)
{
	pthread_mutex_lock(data->m_protect_dead);
	if (*data->dead == 1)
	{
		pthread_mutex_unlock(data->m_protect_dead);
		return (1);
	}
	pthread_mutex_unlock(data->m_protect_dead);
	return (0);
}