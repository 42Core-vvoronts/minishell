/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/12 17:32:18 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Frees a 2D array of strings.
 *
 * @param array The 2D array to free.
 * @return NULL.
 */
static void	*free2d(char **array)
{
	char	**marray;

	marray = array;
	while (*array)
		free(*array++);
	free(marray);
	return (NULL);
}

/**
 * Creates a new result array with an additional string chunk.
 *
 * @param start The start of the string chunk.
 * @param end The end of the string chunk.
 * @param old The old result array.
 * @param i The index to start copying from.
 * @return The new result array.
 */
static char	**create_new_result(char *start, char *end, char **old, size_t i)
{
	char	**new;
	char	**mold;

	mold = old;
	while (*old)
		old++;
	new = (char **)malloc((old - mold + 2) * sizeof(char *));
	old = mold;
	if (!new)
		return (free2d(old));
	while (*old)
		*new++ = *old++;
	*(new + 1) = *old;
	free(mold);
	*new = (char *)malloc((end - start + 1) * sizeof(char));
	if (!*new)
		return (free2d(new - (old - mold)));
	while (start < end)
		(*new)[i++] = *start++;
	(*new)[i] = '\0';
	return (new - (old - mold));
}

/**
 * Adds a chunk of the string to the result array.
 *
 * @param end The current position in the string.
 * @param c The delimiter character.
 * @param old The old result array.
 * @return The updated result array.
 */
static char	**add_chunk(char *end, char c, char **old)
{
	char	*start;
	char	**new;

	while (*end == c && *end)
		end++;
	if (!*end || !old)
		return (old);
	start = end;
	while (*end != c && *end)
		end++;
	new = create_new_result(start, end, old, 0);
	return (add_chunk(end, c, new));
}

// char	**ft_split_old(char const *s, char c)
/**
 * Splits a string into an array of strings using a delimiter character.
 *
 * @param s The string to split.
 * @param c The delimiter character.
 * @return The array of split strings.
 */
char	**ft_split(char const *s, char c)
{
	char	**result;

	result = (char **)malloc(sizeof(char *));
	if (!result)
		return (NULL);
	*result = NULL;
	return (add_chunk((char *)s, c, result));
}

// int	ft_split(t_lst **result, char const *s, char c)
// {
// 	char	**arr;
// 	char	**item;

// 	if (!result || !s)
// 		return (NULL);
// 	*result = NULL;
// 	arr = ft_split_old(s, c);
// 	if (!arr)
// 		return (NULL);
// 	item = arr;
// 	while (*item)
// 	{
// 		if (!lst_add_after(result, lst_get(result, -1), *item))
// 		{
// 			lst_clean(result, NULL);
// 			return ((void *)ft_parrclean(0, free, arr, NULL));
// 		}
// 		item++;
// 	}
// 	free(arr);
// 	return (*result);
// }
