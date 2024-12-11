/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:16:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 02:34:16 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philosophers *philo)
{
	sem_wait(philo->data->forks);
	ft_print_message(FORK, philo);
	sem_wait(philo->data->forks);
	ft_print_message(FORK, philo);
}

void	ft_eat(t_philosophers *philo)
{
	ft_print_message(EATING, philo);
	if (philo->data->eat_counter != -1)
		philo->data->current_eat++;
	usleep(philo->data->time_to_eat * 1000);
	philo->eating_time = ft_get_time();
	philo->next_meal = philo->eating_time
		+ (unsigned int)philo->data->time_to_die;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	*ft_check_death(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	while (1)
	{
		sem_wait(philo->data->death);
		if (philo->next_meal < ft_get_time())
		{
			ft_print_message(DIED, philo);
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
		sem_wait(philo->data->death);
		if ((philo->data->eat_counter != -1)
			&& (philo->data->current_eat >= philo->data->max_eat))
		{
			ft_print_message(DONE, philo);
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
	}
	return (NULL);
}

void	ft_routine(t_philosophers *philo)
{
	pthread_t	death;

	philo->next_meal = ft_get_time() + (unsigned int)philo->data->time_to_die;
	pthread_create(&death, NULL, ft_check_death, philo);
	pthread_detach(death);
	while (1)
	{
		ft_take_fork(philo);
		ft_eat(philo);
		ft_usleep(philo);
		ft_print_message(THINKING, philo);
	}
}