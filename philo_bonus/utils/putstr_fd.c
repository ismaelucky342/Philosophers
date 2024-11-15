/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apollo <apollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:02:05 by apollo            #+#    #+#             */
/*   Updated: 2024/11/14 21:02:33 by apollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"
#include <unistd.h>

void	putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	putstr_fd(const char *str, int fd)
{
	while (*str)
	{
		putchar_fd(*str, fd);
		str++;
	}
}

void	putnbr_fd(size_t num, int fd)
{
	if (num >= 10)
		putnbr_fd(num / 10, fd);
	putchar_fd((num % 10) + '0', fd);
}
