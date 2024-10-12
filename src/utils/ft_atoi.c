/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:32:35 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/12 13:21:25 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_lib.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		num;

	i = 0;
	num = 0;
	while (ft_isdigit(str[i]))
		num = (num * 10) + (str[i++] - '0');
	return (num);
}