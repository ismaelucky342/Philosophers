/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:06:24 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:29:48 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_LIB_H
# define PHILO_LIB_H

/*============================== LIBRARIES ================================*/

# include <sys/time.h>
# include <string.h>
# include <pthread.h>//pthread mutex
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*==============================PHILO ACTIONS==============================*/

# define MEXTRA 4
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4

/*=================================COLORS==================================*/

# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"
# define BOLD    "\033[1m"
# define UNDERLINE "\033[4m"

/*================================STRUCUTRES===============================*/

typedef struct s_mutex
{
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	*mextra;
}	t_mutex;

typedef struct s_input
{
	int	meals;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	number_philososphers;
}	t_input;

typedef struct s_philosophers
{
	long long		last_meal;
	long long		init_time;
	int				philosopher;
	int				*dead;
	int				*number_of_meals;
	t_input			parameters;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*m_protect_eat;
	pthread_mutex_t	*m_protect_dead;
	pthread_mutex_t	*m_protect_last_eat;
	pthread_mutex_t	*m_protect_output;
}	t_philosophers;


/*================================FUNCTIONS=================================*/

int			allocate(pthread_t **th, t_philosophers **info, t_mutex *mtx, t_input prms);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		*procedure(void *arg);
long long	gettime_ms(void);
void		ft_usleep(long long wait, t_philosophers *data);
void		*routine_monitor(void *arg);
int			protect_dead(t_philosophers *data);
int			checker_dead(t_philosophers *data);
void		ft_print(t_philosophers *data, int action);
void		ft_print_death(t_philosophers *data);
int			check_args(char **argv);
void		init_parameters(char **argv, t_input *arg, int argc);
int			init_mutex(t_mutex *mutex, int n);
int			ft_thread(pthread_t *th, t_philosophers *data);
int			init_philosophers(t_philosophers *data, t_mutex mutex, t_input arg);
int			clean_up(pthread_t *th, t_philosophers *info, t_mutex mutex, int n);

#endif
