/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apollo <apollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:46:47 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/19 19:06:25 by apollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void hitman(t_data *data)
{
    int status;
    int i;
    int j;

    i = 0;
    j = 0;
    status = 0;
    while (i < data->num_of_philo)
    {
        waitpid(-1, &status, 0);
        if (status != 0)
        {
            while (++j < data->num_of_philo)
                kill(data->philo[j].pid, SIGINT);
            break ;
        }
        i++;
    }
    sem_close(data->forks);
    sem_close(data->print_semaphore);
    sem_close(data->dead_semaphore);
    sem_close(data->eat_semaphore);
    sem_unlink("/forks");
    sem_unlink("/eat_sem");
    sem_unlink("/print_sem");
    sem_unlink("/dead_sem");

    free(data->philo);
}

void philo_life(t_data *data)
{
    char *str;

    char *id_str = ft_itoa(data->philo->id);
    str = ft_strjoin("/", id_str);
    free(id_str);
    if (str == NULL)
    {
        printf("Error: fail creating sem\n");
        hitman(data);
        return;
    }
    sem_unlink(str);
    
    data->eat_semaphore = sem_open(str, O_CREAT, 0644, 1);
    if (data->eat_semaphore == SEM_FAILED)
    {
        write(2, "Semaphore error\n", 16);
        hitman(data);
        free(str);
        return;
    }
    free(str);
}

void create_processes(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_of_philo)
    {
        data->philo[i].pid = fork();
        if (data->philo[i].pid == 0)  // Hijo: Filósofo
        {
            data->philo[i].id = i + 1;
            philo_life(data);
            routine(data);  // Ejecutar la rutina del filósofo
            exit(0);  // Importante para evitar que el hijo continúe ejecutando el código del padre
        }
        else if (data->philo[i].pid == -1)  // Error al hacer fork
        {
            hitman(data);  // Matar todos los procesos e intentar limpiar
            return;  // Es importante retornar aquí para evitar continuar con un estado inconsistente
        }
        i++;
    }
}
