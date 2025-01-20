/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:05:41 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:37:15 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Cleans the array by applying a function to each element.
 *
 * @param arr Double pointer to the array structure.
 * @param f Function to apply to each element.
 * @return int STOP if the array is empty, CONTINUE otherwise.
 */
static int	clean(t_arr **arr, void *f)
{
	int	(*func)(void *);

	func = (int (*)(void *))f;
	func(*(void **)(*arr)->item);
	return (CONTINUE);
}

/**
 * @brief Cleans the array by applying a function to each
 * element and frees the array.
 *
 * @param arr Double pointer to the array structure.
 * @param f Function to apply to each element.
 * @return t_arr* Always returns NULL.
 */
t_arr	*arr_clean(t_arr **arr, int (*f)(void *))
{
	if (!arr || !*arr)
		return (NULL);
	if (f)
		*arr = arr_iter(arr, clean, f);
	free((*arr)->item);
	free(*arr);
	*arr = NULL;
	return (*arr);
}
