/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 13:26:58 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Locates the last occurrence of 'c' (converted to a char)
 * in the string pointed to by 's'.
 *
 * @param s The string to be scanned.
 * @param c The character to be located.
 * @return A pointer to the located character,
 * or NULL if the character does not appear in the string.
 */
char	*ft_strrchr(const char *s, int c)
{
	char	*mem;

	c = (unsigned char)c;
	mem = NULL;
	while (*s)
	{
		if (*s == c)
			mem = (char *)s;
		s++;
	}
	if (*s == '\0' && c == 0)
		return ((char *)s);
	return (mem);
}
