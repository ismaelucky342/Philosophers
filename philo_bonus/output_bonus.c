/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:07:11 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 15:54:44 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_output(t_philo *philo, char *action)
{
	size_t	time;

	sem_wait(philo->sems->write_sem);
	time = ft_get_time() - philo->times.born_time;
	printf(MG"[%ld] "RE, time);
    printf(G"philo[%d] "RE, philo->id);
    printf("%s\n", action);
	sem_post(philo->sems->write_sem);
}

void	philo_routine(t_philo *philo)
{
	sem_wait(philo->sems->fork_sem);
	ft_output(philo, B "has taken a fork" RE);
	sem_wait(philo->sems->fork_sem);
	ft_output(philo, B "has taken a fork" RE);
	ft_output(philo, RE "is eating" RE);
	sem_wait(philo->sems->die_sem);
	philo->times.last_meal = ft_get_time();
	philo->meals_eaten += 1;
	sem_post(philo->sems->die_sem);
	if (philo->meals_eaten >= philo->must_eat)
		sem_post(philo->sems->meal_sem);
	ft_usleep(philo->times.eat);
	sem_post(philo->sems->fork_sem);
	sem_post(philo->sems->fork_sem);
	ft_output(philo, Y "is sleeping" RE);
	ft_usleep(philo->times.sleep);
	ft_output(philo, MG "is thinking" RE);
}
