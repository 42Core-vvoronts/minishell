/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 13:17:38 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Scans the initial 'n' bytes of the memory area
 * pointed to by 's' for the first instance of 'c'.
 *
 * @param s The memory area to scan.
 * @param c The byte to search for.
 * @param n The number of bytes to scan.
 * @return A pointer to the matching byte or NULL
 * if the byte does not occur in the given memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)(s));
		s++;
	}
	return (NULL);
}
