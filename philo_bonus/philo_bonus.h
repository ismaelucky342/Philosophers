/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:39:41 by dapetros          #+#    #+#             */
/*   Updated: 2024/12/11 15:55:19 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define RE "\033[0m"
# define R "\033[31m"
# define G "\033[32m"
# define Y "\033[33m"
# define B "\033[34m"
# define MG "\033[35m"
# define C "\033[36m"

# define DIE_SEMAPHORE "/die_sem"
# define FORK_SEMAPHORE "/fork_sem"
# define MEAL_SEMAPHORE "/meal_sem"
# define WRITE_SEMAPHORE "/write_sem"

# define PHILOS_MAX_NUMBER 200

typedef pthread_t		t_id;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_sems
{
	sem_t				*die_sem;
	sem_t				*fork_sem;
	sem_t				*meal_sem;
	sem_t				*write_sem;
}						t_sems;

typedef struct s_times
{
	size_t				die;
	size_t				eat;
	size_t				sleep;
	size_t				last_meal;
	size_t				born_time;
}						t_times;

typedef struct s_philo
{
	int					id;
	t_sems				*sems;
	t_times				times;
	int					must_eat;
	int					meals_eaten;
	int					philo_count;
}						t_philo;

typedef struct s_engine
{
	t_sems				*sems;
	t_philo				**philos;
	pid_t				*proc_ids;
	int					philo_count;
}						t_engine;

void					init_philos(t_engine *engine, char **argv, int count);
void					init_sems(t_engine *engine, t_sems *sems, int count);
t_engine				*init_engine(int count);
void					*die_checker(void *ptr);
void					*meal_checker(void *ptr);
void					philo_routine(t_philo *philo);
void					start_simulation(t_engine *engine, int index);
void					launcher(t_engine *engine, int count);
void					error_message(char *text, int signal);
void					ft_hitman(t_engine *engine, char *str,
							bool isParentProc, int signal);
void					ft_output(t_philo *philo, char *action);
size_t					ft_get_time(void);
void					ft_usleep(size_t ms);
size_t					ft_strlen(const char *str);
long					ft_atol(const char *str);

#endif /* PHILO_BONUS_H */
