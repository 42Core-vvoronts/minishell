/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:14:37 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:40:05 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Adds an item from the array to the list.
 *
 * @param arr Pointer to the array.
 * @param lst Pointer to the list.
 * @return int STOP if the item could not be added, CONTINUE otherwise.
 */
static int	add_item(t_arr **arr, void *lst)
{
	if (!lst_add((t_lst **)lst, (*arr)->item, -1))
		return (STOP);
	return (CONTINUE);
}

/**
 * @brief Converts an array to a list.
 * It cleans lst if malloc failed.
 * It doesn't clean arr if malloc failed, because
 * each item can be complex to clean.
 *
 * @param arr Pointer to the array.
 * @return t_lst* Pointer to the new list, or NULL if an error occurred.
 */
t_lst	*arr_to_lst(t_arr **arr)
{
	t_lst	*lst;

	lst = NULL;
	arr_iter(arr, add_item, &lst);
	if (lst_len(&lst) != (*arr)->len)
	{
		lst_clean(&lst, NULL);
		return (NULL);
	}
	free(*arr);
	free((*arr)->item);
	*arr = NULL;
	return (lst);
}
