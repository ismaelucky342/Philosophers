/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:24:55 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:21:04 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_lib.h"

int	handle_single_philosopher(t_philosophers *data)
{
	printf("0  1 has taken a fork\n");
	ft_usleep(data->parameters.t_die, data);
	printf("%d  1 died\n", data->parameters.t_die);
	return (1);
}

int	handle_multiple_philosophers(pthread_t *th, t_philosophers *data)
{
	int	i;

	i = 0;
	while (i < data->parameters.number_philososphers)
	{
		data[i].init_time = gettime_ms();
		pthread_create(&th[i], NULL, &procedure, &data[i]);
		i++;
		if (i == data->parameters.number_philososphers)
			pthread_create(&th[i], NULL, &routine_monitor, data);
	}
	i = 0;
	while (i <= data->parameters.number_philososphers)
		pthread_join(th[i++], NULL);
	return (0);
}

int	ft_thread(pthread_t *th, t_philosophers *data)
{
	if (data->parameters.number_philososphers == 1)
		return (handle_single_philosopher(data));
	return (handle_multiple_philosophers(th, data));
}
