/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_retrieve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:58:17 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:39:06 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Retrieves the item from the array structure and frees the array.
 *
 * @param arr Double pointer to the array structure.
 * @return void* Pointer to the retrieved item.
 */
void	*arr_retrieve(t_arr **arr)
{
	void	*item;

	item = (*arr)->item;
	free(*arr);
	*arr = NULL;
	return (item);
}
