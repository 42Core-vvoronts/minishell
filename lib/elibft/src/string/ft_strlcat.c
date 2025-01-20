/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 13:27:03 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Appends the string 'src' to the end of 'dst'. It will append at most
 * 'dstsize' - strlen(dst) - 1 characters. It will then NUL-terminate, unless
 * 'dstsize' is 0 or the original 'dst' string was longer than 'dstsize'.
 *
 * @param dst The destination buffer.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 * @return The total length of the string it tried to create.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = 0;
	while (*dst && dstsize)
	{
		len++;
		dstsize--;
		dst++;
	}
	while (*src && dstsize > 1)
	{
		*dst++ = *src++;
		len++;
		dstsize--;
		if (dstsize == 1 || !*src)
			*dst = '\0';
	}
	while (*src++)
		len++;
	return (len);
}
