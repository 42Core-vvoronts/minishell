/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/01 17:01:09 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Allocates sufficient memory for a copy of the string 's', does the copy, and
 * returns a pointer to it.
 *
 * @param s The string to duplicate.
 * @return A pointer to the duplicated string. NULL if insufficient memory was
 * available.
 */
char	*ft_strdup(const char *s)
{
	char	*buffer;
	char	*mem;

	if (!s)
		return (NULL);
	buffer = malloc(ft_strlen(s) + 1);
	if (!buffer)
		return (NULL);
	mem = buffer;
	while (*s)
		*buffer++ = *s++;
	*buffer = '\0';
	return (mem);
}
