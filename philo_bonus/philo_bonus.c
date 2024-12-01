/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:07:46 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/01 02:37:16 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_free(t_data *d)
{
	int		i;
	char	name[255];

	if (d == NULL)
		return (0);
	if (d->philo != NULL)
	{
		i = 0;
		while (i < d->num_of_philo)
		{
			if (d->philo[i].id > 0)
				kill(d->philo[i].id, SIGKILL);
			sem_close(d->philo[i].stop_eat); // Cerrar el semáforo
			ft_sem_name("stop_eat", (char *)name, i);
			sem_unlink(name);
			i++;
		}
		free(d->philo);
	}
	sem_close(d->fork);
	sem_close(d->print);
	sem_close(d->mutex);
	sem_close(d->somebody_dead);
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("mutex");
	sem_unlink("somebody_dead");
	return (0);
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
	printf("\033[92m🥳Congratulations: The program has ended successfully!🎉\n");
	printf("\033[92mAll the philosophers eat %d times!\n",
		d->num_of_times_each_philo_must_eat);
	sem_post(d->somebody_dead);
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
	t_data d;

	if (argc == 5 || argc == 6)
	{
		if (ft_parsing(argc, argv, &d) == 1)
		{
			printf("\033[0;31mError: parsing failure\n");
			return (0);
		}
		if (ft_init(&d) == 1)
		{
			printf("\033[0;31mError: Malloc allocation failed\n");
			return (ft_free(&d));
		}
		if (ft_start_process(&d) == 1)
		{
			printf("\033[0;31mError: process failure\n");
			return (ft_free(&d));
		}
		sem_wait(d.somebody_dead);
		ft_free(&d);
	}
	else
		return (ft_error_arg(argc));
	return (0);
}