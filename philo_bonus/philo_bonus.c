/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:37:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/04 00:15:20 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_philo(t_philosophers **philo)
{
	t_philosophers	*tmp;
	int		i;
	int		status;

	tmp = *philo;
	i = 0;
	while (i < tmp->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < tmp->num_philos)
				kill(tmp->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(tmp->block_printf);
	sem_close(tmp->block_fork);
	sem_unlink("/block_print");
	sem_unlink("/block_forks");
	free(tmp->pid);
	free(tmp);
}

int	main(int argc, char **argv)
{
	t_philosophers	*philo;
	int		i;

	philo = init_philo(argc, argv);
	i = -1;
	philo->t_start = ft_get_time();
	while (++i < philo->num_philos)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			ft_error("Error: fork mistake");
		if (philo->pid[i] == 0)
		{
			philo->index = i + 1;
			philo->t_meal = ft_get_time();
			philo_start(philo);
		}
	}
	exit_philo(&philo);
	return (0);
}
