/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:23:38 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/24 23:59:04 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <time.h>
# include <sys/time.h>
# include <pthread.h>
# define SEM_FORKS "/forks_semaphore"
# define SEM_MEALCK "/philo_mealcheck"
# define SEM_WRITING "/philo_writing"
# define SEM_INIT "/philo_init"

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_RED     "\033[31m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_BLUE "\033[34m"

typedef struct s_philosophers
{
	int				nb_meal;
	struct s_global_info	*info;
	long long		t_last_meal;
	int				id;
}					t_philosophers;

typedef struct s_global_info
{
	int			time_eat;
	int			time_sleep;
	int			time_die;
	int			nb_philos;
	int			nb_eat;
	pid_t		*pid;
	long long	first_timestamp;
	sem_t		*forks;
	sem_t		*meal_check;
	sem_t		*writing;
	t_philosophers		philos;
}				t_global_info;

void        philosopher(t_philosophers *philo);
long long	timestamp(void);
void		ft_output(t_philosophers *philo, char *string);
void		init_resource(t_global_info *info, char **argv);
void		destroy_resources(t_global_info *info);
int			ft_atoi(const char *str);
void		ft_usleep(long long time);
void		check_wait(t_philosophers *philo, int time);
int			Hitman(t_philosophers *philo);
int         ft_isdigit(int c);
int         ft_nbr(char **argv);
int         ft_strcmp(const char *str1, const char *str2);

#endif