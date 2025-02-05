/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdups.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:58:45 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 13:06:13 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Frees a 2D array of strings up to a given length.
 *
 * @param result The 2D array of strings to free.
 * @param len The number of strings to free.
 * @return NULL Always returns NULL.
 */
static char	**clean(char **result, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(result[i++]);
	free(result);
	return (NULL);
}

/**
 * @brief Duplicates an array of strings.
 *
 * @param strs The array of strings to duplicate.
 * @return A new array of duplicated strings, or NULL on failure.
 */
char	**ft_strdups(char **strs)
{
	char	**result;
	char	*str;
	size_t	len;
	size_t	i;

	if (!strs)
		return (NULL);
	len = ft_parrlen(strs);
	result = malloc((len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str = ft_strdup(strs[i]);
		if (!str)
			return (clean(result, i));
		result[i] = str;
		i++;
	}
	result[i] = NULL;
	return (result);
}
