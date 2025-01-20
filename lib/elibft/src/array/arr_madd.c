/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_madd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:42:22 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:39:49 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Adds a new item to the array structure by making a copy of the item.
 *
 * @param arr Double pointer to the array structure.
 * @param item Pointer to the item to be added.
 * @param i Index at which the item should be added.
 * @param size_of Size of the item to be added.
 * @return t_arr* Pointer to the updated array structure, or NULL on failure.
 */
t_arr	*arr_madd(t_arr **arr, void *item, int i, size_t size_of)
{
	t_arr	*node;
	void	*result;

	if (!arr || !item || size_of == 0)
		return (NULL);
	result = malloc(size_of);
	if (!result)
		return (NULL);
	ft_memcpy(result, item, size_of);
	node = arr_add(arr, result, i, size_of);
	if (!node)
	{
		free(result);
		return (NULL);
	}
	return (*arr);
}
