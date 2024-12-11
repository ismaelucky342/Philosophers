/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:13:01 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 02:34:16 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_checker_1(t_simulation *simulation, int num, int i)
{
	if (i == 4)
	{
		if (num < 60)
			return (ft_error_msg(simulation,
					R "Error: The time_to_sleep cannot be less than 60 ms" RE,
					1));
		simulation->time_to_sleep = num;
	}
	else if (i == 5)
	{
		if (num == 0)
			simulation->eat_counter = -1;
		else
		{
			simulation->eat_counter = num;
			simulation->current_eat = 0;
			simulation->max_eat = num * simulation->philo_numbers;
		}
	}
	return (0);
}

int	parse_checker_2(t_simulation *simulation, int num, int i)
{
	if (i == 1)
	{
		if (num == 0)
			return (ft_error_msg(NULL,
					R "Error: No philosophers at the table" RE, 1));
		simulation->philo_numbers = num;
	}
	else if (i == 2)
	{
		if (num < 60)
			return (ft_error_msg(simulation,
				R "Error: The time_to_die cannot be less than 60 ms" RE,1));
		simulation->time_to_die = num;
	}
	else if (i == 3)
	{
		if (num < 60)
			return (ft_error_msg(simulation,
				R "Error: The time_to_eat cannot be less than 60 ms" RE,1));
		simulation->time_to_eat = num;
	}
	else
		parse_checker_1(simulation, num, i);
	return (0);
}

int	parse(char **av, t_simulation *simulation)
{
	int	num;
	int	i;

	i = 1;
	while (av[i])
	{
		num = ft_get_number(av[i]);
		if (num == -1)
			return (1);
		if (parse_checker_2(simulation, num, i))
			return (1);
		i++;
	}
	if (i == 5)
	{
		simulation->eat_counter = -1;
		simulation->current_eat = -1;
		simulation->max_eat = -1;
	}
	return (0);
}
