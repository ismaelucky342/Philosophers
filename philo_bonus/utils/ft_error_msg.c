/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:49:04 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/01 02:08:47 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int ft_error_arg(int argc)
{
    if (argc > 6)
        write(1, "\033[1;31mError:\033[0m Too many arguments\n", 37);
    else if (argc < 5)
        write(1, "\033[1;31mError:\033[0m Too few arguments\n", 36);
    return (1);
}