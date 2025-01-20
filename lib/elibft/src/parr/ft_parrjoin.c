/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:04:05 by ipetrov           #+#    #+#             */
/*   Updated: 2024/11/20 15:26:39 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Joins two NULL-terminated arrays of pointers.
 *
 * @param arr1 The first array of pointers.
 * @param arr2 The second array of pointers.
 * @return A new array of pointers containing all elements
 * of arr1 followed by all elements of arr2.
 *         Returns NULL if memory allocation fails.
 */
void	*ft_parrjoin(void *arr1, void *arr2)
{
	size_t	len;
	void	**result;
	void	**mem;
	void	**a1;
	void	**a2;

	len = ft_parrlen(arr1) + ft_parrlen(arr2);
	result = (void **)malloc((len + 1) * sizeof(void *));
	if (!result)
		return (NULL);
	mem = result;
	a1 = (void **)arr1;
	a2 = (void **)arr2;
	while (arr1 && *a1)
		*result++ = *a1++;
	while (arr2 && *a2)
		*result++ = *a2++;
	*result = NULL;
	return ((void *)mem);
}
