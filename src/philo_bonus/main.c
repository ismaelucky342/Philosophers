/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:37:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/23 18:11:27 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>
#include <sys/wait.h>

static int	clean_up(t_global_info *info, sem_t *forks, sem_t *extra)
{
	if (info)
	{
		if (info->dead)
			free(info->dead);
		if (info->number_eats)
			free(info->number_eats);
		free(info);
	}
	if (forks)
		sem_close(forks);
	if (extra)
		sem_close(extra);
	return (0);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!ft_isdigit(av[i][j]) || ft_atoi(av[i]) == 0)
			{
				if (i == 5 && ft_atoi(av[i]) == 0)
					return (0);
				return (-1);
			}
			j++;
		}
		i++;
	}
	if (ft_atoi(av[1]) > 200)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_input			arguments;
	t_global_info	*info;
	sem_t			*forks;
	sem_t			*extra;
	pid_t			*philosophers;
	int				i;

	if (argc < 5 || argc > 6)
		return (printf("Invalid argument number\n"), 1);
	if (check_args(argv) == -1)
		return (printf("Invalid arguments\n"), 1);
	init_params(argv, &arguments, argc);
	memset(&info, 0, sizeof(t_global_info *));
	if (ft_allocate(&info, arguments) != 0)
		return (clean_up(info, forks, extra));
	forks = sem_open("/forks", O_CREAT, 0644, arguments.total_philos);
	extra = sem_open("/extra", O_CREAT, 0644, MUTEX_EXTRA);
	if (forks == SEM_FAILED || extra == SEM_FAILED)
		return (clean_up(info, forks, extra));
	if (init_g_info(info, forks, extra, arguments) != 0)
		return (clean_up(info, forks, extra));
	philosophers = malloc(sizeof(pid_t) * arguments.total_philos);
	if (!philosophers)
		return (clean_up(info, forks, extra));
	i = 0;
	while (i < arguments.total_philos)
	{
		philosophers[i] = fork();
		if (philosophers[i] == 0)
			ft_philosopher(info, i);
		i++;
	}
	i = 0;
	while (i < arguments.total_philos)
		waitpid(philosophers[i++], NULL, 0);
	free(philosophers);
	clean_up(info, forks, extra);
	return (0);
}
