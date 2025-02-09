/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:32:27 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:34:50 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Adds a new item to the array just after a specified index.
 *
 * @param arr Double pointer to the array structure.
 * @param item Pointer to the item to be added.
 * @param i Index after which the item should be added.
 * @param size_of Size of the item to be added.
 * @return t_arr* Pointer to the updated array structure, or NULL on failure.
 */
t_arr	*arr_add(t_arr **arr, void *item, int i, size_t size_of)
{
	t_arr	*node;

	if (!arr)
		return (NULL);
	node = arr_new(&node, item, size_of, 1);
	if (!node)
		return (NULL);
	if (!arr_insert(arr, &node, i))
		return (NULL);
	return (*arr);
}
