/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:08:47 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:34:37 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Initializes a new array structure and attaches the provided item.
 *
 * The function does not duplicate the item, it attaches it directly.
 * The item can be NULL, and in such cases, len and size_of can be 0.
 *
 * @param arr Pointer to the array structure to be initialized.
 * @param item Pointer to the array data.
 * @param size_of Size of each element in the array.
 * @param len Number of elements in the array.
 * @return t_arr* Pointer to the newly created array structure,
 * or NULL on failure.
 */
t_arr	*arr_new(t_arr **arr, void *item, size_t size_of, size_t len)
{
	t_arr	*result;

	if (!item || !arr)
		return (NULL);
	result = malloc(sizeof(t_arr));
	if (!result)
		return (NULL);
	result->item = item;
	result->size_of = size_of;
	result->len = len;
	*arr = result;
	return (*arr);
}
