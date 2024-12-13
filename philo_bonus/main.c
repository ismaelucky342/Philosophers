/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:36:19 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/13 21:29:43 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_free(t_data *d)
{
	int		i;
	char	name[255];

	i = 0;
	while (i < d->num_of_philo)
		kill(d->philo[i++].id, SIGKILL);
	sem_close(d->fork);
	sem_unlink("fork");
	sem_close(d->print);
	sem_unlink("print");
	sem_close(d->mutex);
	sem_unlink("mutex");
	sem_close(d->somebody_dead);
	sem_unlink("somebody_dead");
	if (d->philo)
	{
		i = 0;
		while (i < d->num_of_philo)
		{
			ft_sem_name("stop_eat", (char *)name, i);
			sem_close(d->philo[i].stop_eat); // Close the semaphore
			sem_unlink(name);
			i++;
		}
		free(d->philo);
	}
	return (1);
}

static void	*ft_monitor(void *d_v)
{
	t_data	*d;
	int		i;

	d = (t_data *)d_v;
	i = 0;
	while (i < d->num_of_philo)
	{
		sem_wait(d->philo[i].stop_eat);
		i++;
	}
	sem_wait(d->print);
	printf(G2 "(%lld) [All philosophers eat %d times!]\n" RE, ft_current_time()
		- d->time_start, d->num_of_times_each_philo_must_eat);
	sem_post(d->somebody_dead);
	printf(G2 "[PHILOSOPERS BONUS HAS ENDED SUCCESSFULLY]\n" RE);
	return (NULL);
}

static int	ft_start_process(t_data *d)
{
	pthread_t	tid;
	int			i;

	if (d->num_of_times_each_philo_must_eat > -1)
	{
		if (pthread_create(&tid, NULL, &ft_monitor, (void *)d) != 0)
			return (1);
		pthread_detach(tid);
	}
	d->time_start = ft_current_time();
	i = 0;
	while (i < d->num_of_philo)
	{
		d->philo[i].id = fork();
		if (d->philo[i].id < 0)
			return (1);
		else if (d->philo[i].id == 0)
		{
			ft_routine(&d->philo[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (argc == 5 || argc == 6)
	{
		if (ft_parsing(argc, argv, &d) == 1)
		{
			write(1, R "ERROR: Invalid arguments\n" RE, 18);
			return (0);
		}
		if (ft_init(&d) == 1)
		{
			write(1, R "ERROR: Wrong malloc or semaphore\n" RE, 26);
			return (ft_free(&d));
		}
		if (ft_start_process(&d) == 1)
		{
			write(1, R "ERROR: Process error\n" RE, 15);
			return (ft_free(&d));
		}
		sem_wait(d.somebody_dead);
		ft_free(&d);
	}
	else
		return (ft_error_arg(argc));
	return (0);
}
