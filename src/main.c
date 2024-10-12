/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:02:08 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:20:52 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_lib.h"

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!ft_isdigit(av[i][j]) || ft_atoi(av[i]) == 0)
			{
				if (i == 5 && ft_atoi(av[i]) == 0)
					return (0);
				return (-1);
			}
			j++;
		}
		i++;
	}
	if (ft_atoi(av[1]) > 200)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t		*thread;
	t_input			arguments;
	t_philosophers	*info;
	t_mutex			mutex;

	if (argc < 5 || argc > 6)
		return (printf("Invalid argument number\n"), 1);
	if (check_args(argv) == -1)
		return (printf("Invalid arguments\n"), 1);
	init_parameters(argv, &arguments, argc);
	memset(&mutex, 0, sizeof(t_mutex));
	memset(&info, 0, sizeof(t_philosophers *));
	if (allocate(&thread, &info, &mutex, arguments) != 0)
		return (clean_up(thread, info, mutex, arguments.number_philososphers));
	if (init_mutex(&mutex, arguments.number_philososphers) != 0)
		return (clean_up(thread, info, mutex, arguments.number_philososphers));
	if (init_philosophers(info, mutex, arguments) != 0)
		return (clean_up(thread, info, mutex, arguments.number_philososphers));
	ft_thread(thread, info);
	clean_up(thread, info, mutex, arguments.number_philososphers);
	return (0);
}
