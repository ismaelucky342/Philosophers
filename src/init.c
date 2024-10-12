/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:02:08 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:29:19 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_lib.h"

void	init_parameters(char **argv, t_input *arg, int argc)
{
	arg->number_philososphers = ft_atoi(argv[1]);
	arg->t_die = (ft_atoi(argv[2]));
	arg->t_eat = (ft_atoi(argv[3]));
	arg->t_sleep = (ft_atoi(argv[4]));
	if (argc == 6)
		arg->meals = (ft_atoi(argv[5]));
	else
		arg->meals = 0;
}

int	init_mutex(t_mutex *mutex, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&mutex->mutex_fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < MEXTRA)
	{
		pthread_mutex_init(&mutex->mextra[i], NULL);
		i++;
	}
	{
		pthread_mutex_init(&mutex->mutex_fork[i], NULL);
		i++;
	}
	return (0);
}

static int	init_dead(int **dead)
{
	*dead = (int *)malloc(sizeof(int));
	if (!*dead)
		return (printf("memory allocation error\n"), 1);
	**dead = 0;
	return (0);
}

static int	init_eat(int **eat, t_input arg)
{
	*eat = (int *)malloc(sizeof(int) * arg.number_philososphers);
	if (!*eat)
		return (printf("memory allocation error\n"), 1);
	memset(*eat, 0, sizeof(int) * arg.number_philososphers);
	return (0);
}

int	init_philosophers(t_philosophers *data, t_mutex mutex, t_input arg)
{
	int	*dead;
	int	*eat;
	int	i;

	if (init_dead(&dead) != 0)
		return (1);
	if (init_eat(&eat, arg) != 0)
		return (1);
	i = 0;
	while (i < arg.number_philososphers)
	{
		data[i].philosopher = i + 1;
		data[i].parameters = arg;
		data[i].fork = mutex.mutex_fork;
		data[i].dead = dead;
		data[i].last_meal = 0;
		data[i].number_of_meals = eat;
		data[i].m_protect_output = &mutex.mutex_fork[0];
		data[i].m_protect_dead = &mutex.mutex_fork[1];
		data[i].m_protect_eat = &mutex.mutex_fork[2];
		data[i].m_protect_last_eat = &mutex.mutex_fork[3];
		i++;
	}
	return (0);
}
