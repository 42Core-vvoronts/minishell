/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 13:27:02 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Copies up to 'size' - 1 characters from the string 'src' to 'dest',
 * NUL-terminating the result if 'size' is not 0.
 *
 * @param dest The destination buffer.
 * @param src The source string.
 * @param size The size of the destination buffer.
 * @return The total length of the string it tried to create.
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	const char	*msrc;
	size_t		len;

	len = 0;
	msrc = src;
	while (*msrc++)
		len++;
	if (size == 0)
		return (len);
	while (--size && *src)
		*dest++ = *src++;
	*dest = '\0';
	return (len);
}
