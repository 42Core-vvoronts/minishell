/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:53:13 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:37:22 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Deletes an item from the array at a specified index using function.
 *
 * @param arr Double pointer to the array structure.
 * @param i Index of the item to be deleted.
 * @param f Function to apply to the deleted item.
 * @return t_arr* Always returns NULL.
 */
t_arr	*arr_del(t_arr **arr, int i, int (*f)(void *))
{
	void	*item;

	if (!arr || !*arr || !f)
		return (NULL);
	item = arr_extract(arr, i);
	f(item);
	return (NULL);
}
