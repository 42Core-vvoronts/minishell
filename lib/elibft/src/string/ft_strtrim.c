/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 13:26:58 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Checks if a character is in the given set of characters.
 *
 * @param c The character to check.
 * @param set The set of characters to check against.
 * @return 1 if the character is in the set, 0 otherwise.
 */
static int	is_inset(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

/**
 * Allocates memory for the trimmed string.
 *
 * @param s1 The original string.
 * @param start The starting position of the trimmed string.
 * @return A pointer to the allocated memory.
 */
static char	*allc1d(char const *s1, char *start)
{
	if (*start == '\0')
		return ((char *)malloc((1) * sizeof(char)));
	return ((char *)malloc((s1 - start + 2) * sizeof(char)));
}

/**
 * Allocates and returns a copy of 's1' with the characters specified in 'set'
 * removed from the beginning and the end of the string.
 *
 * @param s1 The string to be trimmed.
 * @param set The reference set of characters to trim.
 * @return The trimmed string, or NULL if the allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	char	*start;
	size_t	len;
	char	*mres;

	len = ft_strlen(s1);
	while (is_inset(*s1, set))
		s1++;
	start = (char *)s1;
	while (*s1)
		s1++;
	while ((is_inset(*s1, set) || (*s1 == '\0' && len)) && s1 != start)
		s1--;
	result = allc1d(s1, start);
	if (!result)
		return (NULL);
	mres = result;
	while (start <= s1 && *start)
		*result++ = *start++;
	*result = '\0';
	return (mres);
}
