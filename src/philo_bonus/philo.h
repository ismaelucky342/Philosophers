/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apollo <apollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:37:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/23 12:04:17 by apollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_DEAD "/sem_dead"

typedef struct s_input
{
	int	total_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	count_meals_required;
}	t_input;

typedef struct s_global_info
{
	int				philo;
	int				*dead;
	long long		last_ate;
	long long		start_time;
	int				*number_eats;
	t_input			params;
	sem_t			*forks;
	sem_t			*sem_print;
	sem_t			*sem_dead;
}	t_global_info;

int			ft_allocate(pthread_t **th, t_global_info **info, t_input prms);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		*philo_routine(void *arg);
long long	ft_get_time(void);
void		ft_usleep(long long wait, t_global_info *data);
void		*routine_monitor(void *arg);
int			verify_dead(t_global_info *data);
int			checker_dead(t_global_info *data);
void		ft_print(t_global_info *data, int action);
void		ft_print_death(t_global_info *data);
int			check_args(char **argv);
void		init_params(char **argv, t_input *arg, int argc);
int			init_semaphores(t_global_info *data);
int			ft_world(pthread_t *th, t_global_info *data);
int			init_g_info(t_global_info *data, t_input arg);

#endif
