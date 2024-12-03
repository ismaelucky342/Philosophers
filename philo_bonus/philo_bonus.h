/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:37:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/04 00:16:03 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "semaphore.h"
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philosophers
{
	int				num_philos;
	int				num_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	int				num_eat_count;
	int				stop;
	int				died;
	int				*pid;
	sem_t			*block_printf;
	sem_t			*block_fork;
	long long int	t_start;
	int				index;
	long long int	t_meal;
	pthread_t		check_monitor;
}					t_philosophers;

// init
t_philosophers		*init_philo(int argc, char **argv);

// unity
void				philo_start(t_philosophers *philo);
void				*check_monitor(void *args);

int					ft_atol(const char *str);
int					ft_error(char *str);
long long			ft_get_time(void);
void				ft_usleep(long long time, t_philosophers *philo);
void				philo_print(t_philosophers *philo, char *str);
#endif
