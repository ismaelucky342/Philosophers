/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:37:37 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 14:11:27 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	parse_check(int argc, char **argv)
{
	int		i;
	long	num;

	i = 0;
	if (argc < 5 || argc > 6)
		error_message("[Argument Count ERROR]\n", 1);
	while (++i < argc)
	{
		num = ft_atol(argv[i]);
		if (i == 1 && (num < 1 || num > PHILOS_MAX_NUMBER))
			error_message("[Argument ERROR]\n", 1);
		else if (i == 5 && (num < 1 || num > INT_MAX))
			error_message("[Argument ERROR]\n", 1);
		else if (i != 1 && i != 5 && (num < 1 || num > INT_MAX))
			error_message("[Argument ERROR]\n", 1);
	}
}

int	main(int argc, char **argv)
{
	t_engine	*engine;

	parse_check(argc, argv);
	engine = init_engine(ft_atol(argv[1]));
	init_philos(engine, argv, engine->philo_count);
	launcher(engine, engine->philo_count);
	ft_hitman(engine, NULL, true, EXIT_SUCCESS);
	return (0);
}
