/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:07:46 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/01 02:09:15 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print_message(t_data *d, int pid, char *msg)
{
	long long	time_work;

	time_work = ft_current_time() - d->time_start;
	sem_wait(d->print);
	printf("\033[36m%lld \033[0;32mphilo[%d] %s\n", time_work, pid, msg);
	sem_post(d->print);
}
