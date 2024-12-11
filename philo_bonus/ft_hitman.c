/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hitman.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:26:17 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 15:55:09 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_hitman(t_engine *engine, char *str, bool isParentProc, int signal)
{
	int	i;

	i = -1;
	if (isParentProc)
	{
		while (++i < engine->philo_count)
			if (engine->proc_ids[i] != -1)
				kill(engine->proc_ids[i], SIGKILL);
	}
	if (engine->sems->die_sem != SEM_FAILED)
		sem_close(engine->sems->die_sem);
	if (engine->sems->fork_sem != SEM_FAILED)
		sem_close(engine->sems->fork_sem);
	if (engine->sems->meal_sem != SEM_FAILED)
		sem_close(engine->sems->meal_sem);
	if (engine->sems->write_sem != SEM_FAILED)
		sem_close(engine->sems->write_sem);
	i = -1;
	while (++i < engine->philo_count)
		free(engine->philos[i]);
	free(engine->sems);
	free(engine->philos);
	free(engine->proc_ids);
	free(engine);
	error_message(str, signal);
}
