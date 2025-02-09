/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 13:27:05 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Locates the first occurrence of 'c' (converted to a char) in the string
 * pointed to by 's'. The terminating null character is considered to be part
 * of the string.
 *
 * @param s The string to search.
 * @param c The character to locate.
 * @return A pointer to the located character, or NULL if the character does
 * not appear in the string.
 */
char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char)c;
	while (*s != c && *s)
		s++;
	if (*s == '\0' && c == 0)
		return ((char *)s);
	if (!*s)
		return (NULL);
	return ((char *)s);
}
