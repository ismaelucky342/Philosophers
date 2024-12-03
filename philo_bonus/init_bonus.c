/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:37:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/04 00:13:40 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philosophers	*init_data(int argc, char **argv)
{
	t_philosophers	*tmp;

	tmp = (t_philosophers *)malloc(sizeof(t_philosophers));
	if (!tmp)
		ft_error("Error: Failed to malloc philo");
	tmp->num_philos = ft_atol(argv[1]);
	tmp->num_forks = tmp->num_philos;
	tmp->t_die = ft_atol(argv[2]);
	tmp->t_eat = ft_atol(argv[3]);
	tmp->t_sleep = ft_atol(argv[4]);
	if (tmp->num_philos < 1 || tmp->num_philos > 250 || tmp->t_die == -1 || \
		tmp->t_eat == -1 || tmp->t_sleep == -1)
		ft_error("Error: Wrong arguments");
	tmp->num_eat = -1;
	if (argc == 6)
	{
		tmp->num_eat = ft_atol(argv[5]);
		if (tmp->num_eat == -1)
			ft_error("Error: Wrong arguments");
	}
	tmp->num_eat_count = 0;
	tmp->stop = 0;
	tmp->died = 0;
	return (tmp);
}

t_philosophers	*init_philo(int argc, char **argv)
{
	t_philosophers	*tmp;

	if (argc < 5 || argc > 6)
		ft_error("Error: Wrong number of arguments");
	tmp = init_data(argc, argv);
	tmp->pid = (int *)malloc(sizeof(int) * tmp->num_forks);
	if (!tmp->pid)
		ft_error("Error: malloc error (init pid)");
	sem_unlink("/block_print");
	sem_unlink("/block_forks");
	tmp->block_printf = sem_open("/block_print", O_CREAT, 0644, 1);
	tmp->block_fork = sem_open("/block_forks", O_CREAT, \
								0644, tmp->num_forks);
	if (tmp->block_printf == SEM_FAILED || tmp->block_fork == SEM_FAILED)
		ft_error("Error: semaphore open error");
	if (tmp->block_printf == NULL || tmp->block_fork == NULL)
		ft_error("Error: semaphore initialization error");
	return (tmp);
}
