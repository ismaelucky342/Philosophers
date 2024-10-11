/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apollo <apollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:16:41 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/11 20:04:58 by apollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_lib.h"

// Función para obtener el tiempo actual en milisegundos
long long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000LL + current_time.tv_usec / 1000LL);
}

// Función principal del programa
int	main(int argc, char *argv[])
{
	t_simulation	sim;
	size_t			i;

	// Verifica la entrada del usuario
	if (!check_input(argc, argv))
	{
		return (input_error(), 0);
	}
	// Inicializa la simulación
	initialize_simulation(&sim, ft_atoi(argv[1]), argc, argv);
	// Bloquea el mutex de muerte
	pthread_mutex_lock(&sim.death_mutex);
	// Espera a que todos los hilos terminen
	i = 0;
	while (i < sim.number_of_philosophers)
	{
		pthread_join(sim.philosophers[i].thread_id, NULL);
		i++;
	}
	// Finaliza la simulación
	ft_exit(&sim, sim.number_of_philosophers);
	return (0);
}
