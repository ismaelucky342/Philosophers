/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:18:38 by ismherna          #+#    #+#             */
/*   Updated: 2024/07/18 09:29:31 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_lib.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	ft_atoi(char *s)
{
	size_t	i;
	int		v;
	int		sy;

	i = 0;
	v = 0;
	sy = 1;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sy = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		v = (v * 10) + (s[i] - '0');
		i++;
	}
	return (sy * v);
}
