/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:15:30 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/04 00:15:35 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_monitor(void *args)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)args;
	while (!philo->stop)
	{
		usleep(100);
		if (ft_get_time() - philo->t_meal > philo->t_die)
		{
			philo->died = 1;
			sem_wait(philo->block_printf);
			printf("%lld %d %s\n", \
					ft_get_time() - philo->t_start, philo->index, "died");
			philo->stop = 1;
			break ;
		}
		if (philo->num_eat != -1 && philo->num_eat_count >= philo->num_eat)
		{
			philo->stop = 1;
			break ;
		}
	}
	if (philo->died)
		exit (1);
	else
		exit (0);
}

void	philo_start(t_philosophers *philo)
{
	if (pthread_create(&philo->check_monitor, \
			NULL, &check_monitor, philo))
		ft_error("Error: Failed to create the thread");
	if (philo->index % 2 == 1)
		usleep(1000);
	while (1)
	{
		philo_print(philo, "is thinking");
		sem_wait(philo->block_fork);
		philo_print(philo, "has taken a fork");
		sem_wait(philo->block_fork);
		philo_print(philo, "has taken a fork");
		philo_print(philo, "is eating");
		ft_usleep(philo->t_eat, philo);
		philo->t_meal = ft_get_time();
		sem_post(philo->block_fork);
		sem_post(philo->block_fork);
		philo->num_eat_count += 1;
		philo_print(philo, "is sleeping");
		ft_usleep(philo->t_sleep, philo);
	}
	if (pthread_join(philo->check_monitor, NULL))
		ft_error("Error: Failed to join the thread");
}