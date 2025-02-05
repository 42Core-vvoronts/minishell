/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:58:14 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:38:57 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Iterates over the array and applies a function to each element.
 *
 * @param arr Double pointer to the array structure.
 * @param f Function to apply to each element.
 * @param param Additional parameter to pass to the function.
 * @return t_arr* Pointer to the array structure after iteration.
 */
t_arr	*arr_iter(t_arr **arr, int (*f)(t_arr **, void *), void *param)
{
	size_t	len;
	void	*mem;

	if (!arr || !*arr || !f)
		return (NULL);
	len = (*arr)->len;
	mem = (*arr)->item;
	while (len--)
	{
		if (!f(arr, param))
			break ;
		if (*arr)
			(*arr)->item = (unsigned char *)(*arr)->item + (*arr)->size_of;
	}
	if (*arr)
		(*arr)->item = mem;
	return (*arr);
}
