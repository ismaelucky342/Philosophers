/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apollo <apollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:16:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/11 20:04:00 by apollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_lib.h"

static void	initialize_philosopher(t_philosopher *ph)
{
	if (ph->thread_id % 2 == 0)
		ft_usleep(ph->pointer_program->eating_duration / 10);
	ph->last_meal = get_current_time();
	ph->time_remaining = ph->last_meal
		+ ph->pointer_program->death_time_threshold;
	if (pthread_create(&ph->processor_thread, NULL, alive_checker, ph) != 0)
		return ;
}

void	*philosopher_thread(void *arg)
{
	t_philosopher	*ph;
	long long		i;

	ph = arg;
	i = -1;
	initialize_philosopher(ph);
	while (ph->pointer_program->required_meals == -1
		|| ++i < ph->pointer_program->required_meals)
	{
		perform_actions(ph->pointer_program, ph);
	}
	return (NULL);
}
