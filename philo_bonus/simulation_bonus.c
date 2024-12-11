/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:46:00 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 15:56:38 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *die_checker(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	while (true)
	{
		sem_wait(philo->sems->die_sem);
		if (ft_get_time() - philo->times.last_meal > philo->times.die)
		{
			ft_output(philo, R "has died" RE);
			sem_wait(philo->sems->write_sem);
			sem_post(philo->sems->meal_sem);
			exit(EXIT_SUCCESS);
		}
		sem_post(philo->sems->die_sem);
		usleep(1000); // Add a small delay to allow other threads to access the shared data
	}
	return NULL;
}

void *meal_checker(void *ptr)
{
	t_engine *engine;
	int finished;

	finished = 0;
	engine = (t_engine *)ptr;
	while (true)
	{
		sem_wait(engine->sems->meal_sem);
		++finished;
		if (finished >= engine->philo_count)
			ft_hitman(engine, NULL, true, EXIT_SUCCESS);
	}
	return NULL;
}

void start_simulation(t_engine *engine, int index)
{
	t_id die_checker_id;
	t_philo *philo;

	philo = engine->philos[index];
	if (pthread_create(&die_checker_id, NULL, die_checker, philo) != 0 ||
		pthread_detach(die_checker_id) != 0)
		ft_hitman(engine, "[Thread ERROR]\n", false, EXIT_FAILURE);
	philo->times.born_time = ft_get_time();
	philo->times.last_meal = ft_get_time();
	while (true)
		philo_routine(philo);
}

void launcher(t_engine *engine, int count)
{
	t_id meal_checker_id;
	t_philo **philos;
	pid_t id;
	int i;

	i = -1;
	philos = engine->philos;
	if (philos[0]->must_eat > 0)
	{
		if (pthread_create(&meal_checker_id, NULL, meal_checker, engine) != 0)
			ft_hitman(engine, "[Thread Open ERROR]\n", true, 1);
		if (pthread_detach(meal_checker_id) != 0)
			ft_hitman(engine, "[Thread Detach ERROR]\n", true, 1);
	}
	while (++i < count)
	{
		id = fork();
		engine->proc_ids[i] = id;
		if (id == -1)
			ft_hitman(engine, "[Fork ERROR]\n", true, 1);
		if (id == 0)
			start_simulation(engine, i);
	}
	waitpid(-1, NULL, 0);
}
