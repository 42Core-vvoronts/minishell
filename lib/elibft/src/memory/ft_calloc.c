/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:47:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/24 04:03:15 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Allocates memory for an array of 'num' elements of 'size' bytes each and
 * initializes all bytes in the allocated storage to zero.
 *
 * @param num Number of elements.
 * @param size Size of each element.
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
 */
void	*ft_calloc(size_t num, size_t size)
{
	size_t			total;
	unsigned char	*result;

	if (num == 0 || size == 0)
		return ((void *)malloc(0));
	if (num > SIZE_MAX / size)
		return (NULL);
	total = num * size;
	result = malloc(total);
	if (!result)
		return (NULL);
	while (total--)
		*result++ = 0;
	return ((void *)(result - (num * size)));
}
