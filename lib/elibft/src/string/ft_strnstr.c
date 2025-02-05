/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 13:27:00 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Checks if the beginning of 'haystack' matches 'needle'
 * for up to 'len' characters.
 *
 * @param haystack The string to be scanned.
 * @param needle The small string to be searched within the haystack string.
 * @param len The maximum number of characters to be compared.
 * @return 1 if 'needle' is found at the beginning of 'haystack', 0 otherwise.
 */
static	int	is_needle(const char *haystack, const char *needle, size_t len)
{
	while (len-- && *haystack && *needle)
	{
		if (*haystack != *needle)
			return (0);
		haystack++;
		needle++;
	}
	if (*needle)
		return (0);
	return (1);
}

/**
 * Locates the first occurrence of the null-terminated string 'needle'
 * in the string 'haystack',
 * where not more than 'len' characters are searched.
 *
 * @param haystack The string to be scanned.
 * @param needle The small string to be searched with-in haystack string.
 * @param len The maximum number of characters to be searched.
 * @return A pointer to the first character of the first occurrence of 'needle',
 *         or NULL if 'needle' is not found.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && len)
	{
		if (is_needle(haystack, needle, len))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
