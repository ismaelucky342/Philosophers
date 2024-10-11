/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:16:41 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/11 10:42:20 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_lib.h"

long long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000LL + current_time.tv_usec / 1000LL);
}

int	main(int argc, char *argv[])
{
	t_simulation	sim;

	if (!check_input(argc, argv))
	{
		return (input_error(), 0);
	}
	initialize_simulation(&sim, ft_atoi(argv[1]), argc, argv);
	pthread_mutex_lock(&sim.death_mutex);
	ft_exit(&sim, sim.number_of_philosophers);
	return (0);
}
