/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:13:01 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 02:37:46 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_create_process(t_simulation *simulation, t_philosophers *philo)
{
	int	i;

	i = 0;
	while (i < simulation->philo_numbers)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			ft_routine(philo + i);
			exit(0);
		}
		i++;
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	t_simulation	simulation;
	t_philosophers			*philo;

	if (ac == 5 || ac == 6)
	{
		if (parse(av, &simulation))
			return (1);
		philo = ft_philosophers_init(&simulation);
		simulation.start = ft_get_time();
		ft_create_semaphores(&simulation);
		sem_wait(simulation.stop);
		ft_create_process(&simulation, philo);
		sem_wait(simulation.stop);
		ft_destroy_all(&simulation, philo);
	}
	else
		printf("Error: Too many arguments\n");
	return (0);
}
