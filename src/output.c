/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:02:08 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:32:30 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_lib.h"

static void print_eat(t_philosophers *data)
{
    pthread_mutex_lock(data->m_protect_last_eat);
    data->last_meal = gettime_ms() - data->init_time; 
    pthread_mutex_unlock(data->m_protect_last_eat);
    printf(GREEN "%lld %d is eating\n" RESET, data->last_meal, data->philosopher);
    
    pthread_mutex_lock(data->m_protect_eat);
    data->number_of_meals[data->philosopher - 1] += 1;
    pthread_mutex_unlock(data->m_protect_eat);
}

void ft_print_death(t_philosophers *data)
{
    pthread_mutex_lock(data->m_protect_output);
    printf(RED "%lld %d died\n" RESET, gettime_ms() - data->init_time, data->philosopher); // Changed start_time to init_time
    pthread_mutex_unlock(data->m_protect_output);
}

void ft_print(t_philosophers *data, int action)
{
    pthread_mutex_lock(data->m_protect_output);
    if (checker_dead(data) == 0)
    {
        if (action == FORK)
            printf(YELLOW "%lld %d has taken a fork\n" RESET, gettime_ms() - data->init_time, data->philosopher); // Changed start_time to init_time
        else if (action == EAT)
            print_eat(data);
        else if (action == SLEEP)
            printf(BLUE "%lld %d is sleeping\n" RESET, gettime_ms() - data->init_time, data->philosopher); // Changed start_time to init_time
        else if (action == THINK)
            printf(MAGENTA "%lld %d is thinking\n" RESET, gettime_ms() - data->init_time, data->philosopher); // Changed start_time to init_time
    }
    pthread_mutex_unlock(data->m_protect_output);
}
