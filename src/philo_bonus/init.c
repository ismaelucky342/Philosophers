/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:33:45 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/24 23:34:59 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_resource(t_global_info *info, char **argv)
{
	if (ft_nbr(argv))
		(printf("NO es un argumento valido"), exit(0));
	info->time_die = ((info->nb_philos = ft_atoi(argv[1])), ft_atoi(argv[2]));
	info->time_sleep = ((info->time_eat = ft_atoi(argv[3])), ft_atoi(argv[4]));
	if (info->nb_philos <= 0 || info->nb_philos > 200 || \
	info->time_die < 60 || info->time_sleep < 60 || info->time_eat < 60)
		(printf("NO es un argumento valido\n"), exit(0));
	if (argv[5])
	{
		info->nb_eat = ft_atoi(argv[5]);
		if (info->nb_eat <= 0)
			(printf("NO es un argumento valido\n"), exit(1));
	}
	else
		info->nb_eat = 0;
	(sem_unlink(SEM_FORKS), sem_unlink(SEM_MEALCK));
	(sem_unlink(SEM_WRITING));
	info->forks = sem_open(SEM_FORKS, O_CREAT, 0644, info->nb_philos);
	info->meal_check = sem_open(SEM_MEALCK, O_CREAT, 0644, 1);
	info->writing = sem_open(SEM_WRITING, O_CREAT, 0644, 1);
	info->pid = malloc(sizeof(pid_t) * (info->nb_philos + 1));
}

void	destroy_resources(t_global_info *info)
{
	int	status;
	int	i;

	i = 0;
	while (i < info->nb_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < info->nb_philos)
				kill(info->pid[i], 15);
			break ;
		}
		i++;
	}
	sem_close(info->forks);
	sem_close(info->meal_check);
	sem_close(info->writing);
	sem_unlink(SEM_FORKS);
	(sem_unlink(SEM_MEALCK), sem_unlink(SEM_WRITING));
	free(info->pid);
}
