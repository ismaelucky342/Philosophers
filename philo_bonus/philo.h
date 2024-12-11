/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:13:01 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 02:36:38 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

// Colors
#define RE   "\033[0m"
#define R     "\033[31m"
#define G   "\033[32m"
#define Y  "\033[33m"
#define B    "\033[34m"
#define MG "\033[35m"
#define CY    "\033[36m"
#define W   "\033[37m"

# define YES 1
# define NO 0
# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5
# define DONE 6

typedef struct s_simulation
{
	sem_t			*forks;
	sem_t			*message;
	sem_t			*death;
	sem_t			*stop;
	unsigned int	start;
	int				philo_numbers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_counter;
	int				max_eat;
	int				current_eat;
}				t_simulation;

typedef struct s_philosophers
{
	t_simulation	*data;
	pid_t			pid;
	unsigned int	eating_time;
	unsigned int	next_meal;
	int				index;
	int				is_dead;
	int				eat_counter;
}				t_philosophers;

unsigned int	ft_get_time(void);
void			ft_routine(t_philosophers *philo);
void			ft_eat(t_philosophers *philo);
void			ft_usleep(t_philosophers *philo)
int				ft_get_number(char *arg);
void			*ft_check_death(void *arg);
void			ft_take_fork(t_philosophers *philo);
void			ft_print_message(int id, t_philosophers *philo);
t_philosophers			*ft_philosophers_init(t_simulation *simulation);
void			ft_create_semaphores(t_simulation *simulation);
int				parse(char **av, t_simulation *simulation);
int				parse_checker_1(t_simulation *simulation, int num, int i);
int				parse_checker_2(t_simulation *simulation, int num, int i);
void			ft_destroy_all(t_simulation *simulation, t_philosophers *philo);
void			ft_for_each_philo(t_simulation *simulation, t_philosophers *philo,
					int i);
int				ft_error_msg(t_simulation *simulation, char *message, int ret);

#endif
