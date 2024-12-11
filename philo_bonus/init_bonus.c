/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:45:37 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 15:54:54 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philos(t_engine *engine, char **argv, int count)
{
	t_philo	**philos;
	int		i;

	i = -1;
	philos = engine->philos;
	while (++i < count)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philos[i])
			ft_hitman(engine, "[Malloc ERROR]\n", true, EXIT_FAILURE);
		philos[i]->id = i + 1;
		philos[i]->sems = engine->sems;
		philos[i]->times.die = ft_atol(argv[2]);
		philos[i]->times.eat = ft_atol(argv[3]);
		philos[i]->times.sleep = ft_atol(argv[4]);
		philos[i]->times.last_meal = ft_get_time();
		philos[i]->times.born_time = ft_get_time();
		philos[i]->must_eat = -1;
		if (argv[5])
			philos[i]->must_eat = ft_atol(argv[5]);
		philos[i]->meals_eaten = 0;
		philos[i]->philo_count = count;
	}
}

void	init_sems(t_engine *engine, t_sems *sems, int count)
{
	sems->die_sem = sem_open(DIE_SEMAPHORE, O_CREAT | O_EXCL, 0644, 1);
	sems->fork_sem = sem_open(FORK_SEMAPHORE, O_CREAT | O_EXCL, 0644, count);
	sems->meal_sem = sem_open(MEAL_SEMAPHORE, O_CREAT | O_EXCL, 0644, 0);
	sems->write_sem = sem_open(WRITE_SEMAPHORE, O_CREAT | O_EXCL, 0644, 1);
	if (sems->die_sem == SEM_FAILED || sems->fork_sem == SEM_FAILED
		|| sems->meal_sem == SEM_FAILED || sems->write_sem == SEM_FAILED)
		ft_hitman(engine, "[Semaphore Open ERROR]\n", true, EXIT_FAILURE);
	if (sem_unlink(DIE_SEMAPHORE) == -1 || sem_unlink(FORK_SEMAPHORE) == -1
		|| sem_unlink(MEAL_SEMAPHORE) == -1 || sem_unlink(WRITE_SEMAPHORE) == -1)
		ft_hitman(engine, "[Semaphore Unlink ERROR]\n", true, EXIT_FAILURE);
}

t_engine	*init_engine(int count)
{
	t_engine	*engine;
	t_philo		**philos;
	pid_t		*proc_ids;
	t_sems		*sems;
	int			i;

	i = -1;
	engine = (t_engine *)malloc(sizeof(t_engine));
	philos = (t_philo **)malloc(sizeof(t_philo *) * count);
	proc_ids = (pid_t *)malloc(sizeof(pid_t) * count);
	sems = (t_sems *)malloc(sizeof(t_sems));
	if (!engine || !philos || !proc_ids || !sems)
		ft_hitman(engine, "[Malloc ERROR]\n", false, EXIT_FAILURE);
	engine->sems = sems;
	engine->philos = philos;
	engine->proc_ids = proc_ids;
	engine->philo_count = count;
	while (++i < count)
	{
		proc_ids[i] = -1;
		philos[i] = NULL;
	}
	init_sems(engine, sems, count);
	return (engine);
}
