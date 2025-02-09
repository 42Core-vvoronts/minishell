/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 13:26:44 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Writes 'len' zeroed bytes to the string 's'.
 *
 * @param s The string to be zeroed.
 * @param len The number of bytes to write.
 */
void	ft_bzero(void *s, size_t len)
{
	char	*p;

	p = s;
	while (len)
	{
		*p = 0;
		len--;
		p++;
	}
}
