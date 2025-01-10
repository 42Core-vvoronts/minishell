/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:45:20 by vvoronts          #+#    #+#             */
/*   Updated: 2024/09/04 09:22:02 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	number;
	char			c;

	number = (unsigned int)(n);
	if (n < 0)
	{
		write(fd, "-", 1);
		number = (unsigned int)(-n);
	}
	if (number < 10)
	{
		c = number + 48;
		write(fd, &c, 1);
		return ;
	}
	ft_putnbr_fd(number / 10, fd);
	ft_putnbr_fd(number % 10, fd);
}
