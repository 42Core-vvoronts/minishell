/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:13:30 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/27 10:48:15 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Allocates sufficient memory for a copy of the string 's',
 * does the copy of n elements, and
 * returns a pointer to new string.
 *
 * @param s pointer to start of the string
 * @param len length to copy
 * @return A pointer to the duplicated string. NULL if insufficient memory was
 * available.
 */
char	*ft_strndup(char *s, int len)
{
	char	*dest;
	char	*mem;

	if (!s)
		return (NULL);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	mem = dest;
	while (*s && len--)
		*dest++ = *s++;
	*dest = '\0';
	return (mem);
}
