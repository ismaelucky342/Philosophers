/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:30:12 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/25 00:00:49 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_output(t_philosophers *philo, char *string)
{
	sem_wait(philo->info->writing);
	if (ft_strcmp(string, "is eating") == 0)
		printf(COLOR_GREEN);
	else if (ft_strcmp(string, "is sleeping") == 0)
		printf(COLOR_CYAN);
	else if (ft_strcmp(string, "is thinking") == 0)
		printf(COLOR_YELLOW);
	else if (ft_strcmp(string, "died") == 0)
		printf(COLOR_RED);
	else
		printf(COLOR_RESET);
	printf("%lli ", timestamp() - philo->info->first_timestamp);
	printf("%i ", philo->id + 1);
	printf("%s\n", string);
	printf(COLOR_RESET);
	sem_post(philo->info->writing);
	return ;
}

int	Hitman(t_philosophers *philo)
{
	sem_wait(philo->info->meal_check);
	if ((timestamp() - (philo->t_last_meal)) > philo->info->time_die)
	{
		sem_wait(philo->info->writing);
		printf(COLOR_RED "%lli ", timestamp() - philo->info->first_timestamp);
		printf("%i ", philo->id + 1);
		printf("is dead" COLOR_RESET "\n");
		return (-1);
	}
	sem_post(philo->info->meal_check);
	return (1);
}

void	*checker_dead(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	while (Hitman(philo) != -1)
		usleep(100);
	free(philo->info->pid);
	exit(1);
	return (NULL);
}

void	philo_eat(t_philosophers *philo)
{
	ft_usleep(1);
	sem_wait(philo->info->forks);
	ft_output(philo, COLOR_YELLOW "has taken a fork" COLOR_RESET);
	ft_usleep(1);
	sem_wait(philo->info->forks);
	ft_output(philo, COLOR_YELLOW "has taken a fork" COLOR_RESET);
	sem_wait(philo->info->meal_check);
	philo->t_last_meal = timestamp();
	sem_post(philo->info->meal_check);
	ft_output(philo, COLOR_GREEN "is eating" COLOR_RESET);
	check_wait(philo, philo->info->time_eat);
	philo->nb_meal++;
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	philosopher(t_philosophers *philo)
{
	t_global_info	*info;
	pthread_t		thread;

	info = philo->info;
	philo->t_last_meal = timestamp();
	pthread_create(&thread, NULL, checker_dead, philo);
	if (philo->id % 2)
		ft_usleep(50);
	while (1)
	{
		philo_eat(philo);
		ft_output(philo, COLOR_CYAN "is sleep" COLOR_RESET);
		check_wait(philo, info->time_sleep);
		ft_output(philo, COLOR_BLUE "is thinking" COLOR_RESET);
		if (info->nb_eat != 0 && philo->nb_meal >= info->nb_eat)
			(pthread_join(thread, NULL), exit(0));
	}
	pthread_join(thread, NULL);
	exit(1);
}
