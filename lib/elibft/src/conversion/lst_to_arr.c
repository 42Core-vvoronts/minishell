/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:24:46 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:44:12 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Adds an item from the list to the array.
 *
 * @param lst Pointer to the list.
 * @param arr Pointer to the array.
 * @return int STOP if the item could not be added, CONTINUE otherwise.
 */
static int	add_item(t_lst **lst, void *arr)
{
	void	**item;

	item = malloc(sizeof(void *));
	if (!item)
		return (STOP);
	*item = (*lst)->item;
	if (!item || !arr_add(arr, item, -1, sizeof(void **)))
		return (STOP);
	return (CONTINUE);
}

/**
 * @brief Converts a list to an array.
 * It cleans arr if malloc failed.
 *
 * @param lst Pointer to the list.
 * @return t_arr* Pointer to the new array, or NULL if an error occurred.
 */
t_arr	*lst_to_arr(t_lst **lst)
{
	t_arr	*arr;

	arr = NULL;
	*lst = lst_get(lst, 0);
	lst_iter(lst, add_item, &arr);
	if (lst_len(lst) != arr->len)
	{
		arr_clean(&arr, NULL);
		return (NULL);
	}
	lst_clean(lst, NULL);
	return (arr);
}
