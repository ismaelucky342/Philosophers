/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:39:01 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:24:10 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_lib.h"

int	allocate(pthread_t **th, t_philosophers **info, t_mutex *mtx, t_input prms)
{
	*th = (pthread_t *)malloc(sizeof(pthread_t) * (prms.number_philososphers
				+ 1));
	if (!*th)
		return (printf("memory allocation error\n"), 1);
	*info = (t_philosophers *)malloc(sizeof(t_philosophers)
			* prms.number_philososphers);
	if (!*info)
		return (printf("memory allocation error\n"), 1);
	mtx->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (prms.number_philososphers));
	if (!mtx->mutex_fork)
		return (printf("memory allocation error\n"), 1);
	mtx->mextra = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * MEXTRA);
	if (!mtx->mextra)
		return (printf("memory allocation error\n"), 1);
	return (0);
}
