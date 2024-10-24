/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_v1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:26:18 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/24 23:53:28 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
    t_global_info	info;
    int		i;

    if (argc != 5 && argc != 6)
        return (1);
    init_resource(&info, argv);
    if (info.forks == SEM_FAILED || info.meal_check == SEM_FAILED || \
        info.writing == SEM_FAILED)
        (printf("sem_open failed"), exit(EXIT_FAILURE));
    i = -1;
    info.first_timestamp = timestamp();
    while (++i < info.nb_philos)
    {
        info.pid[i] = fork();
        if (info.pid[i] == -1)
            exit(EXIT_FAILURE);
        else if (info.pid[i] == 0)
        {
            info.philos.info = &info;
            info.philos.nb_meal = 0;
            info.philos.id = i;
            philosopher(&info.philos);
        }
    }
    return (destroy_resources(&info), 0);
}