/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 13:26:57 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Allocates and returns a substring from the string 's'.
 * The substring begins at index 'start' and is of maximum size 'len'.
 *
 * @param s The string from which to create the substring.
 * @param start The start index of the substring.
 * @param len The maximum length of the substring.
 * @return The substring, or NULL if the allocation fails.
 */
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*result;
	char	*mem;
	size_t	slen;

	slen = ft_strlen(s);
	if (start > slen || len == 0)
	{
		result = (char *)malloc((1) * sizeof(char));
		if (!result)
			return (NULL);
		*result = '\0';
		return (result);
	}
	if (len > slen - start)
		len = slen - start;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	mem = result;
	s = s + start;
	while (len--)
		*result++ = *s++;
	*result = '\0';
	return (mem);
}
