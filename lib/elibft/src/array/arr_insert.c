/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:52:14 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:38:44 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

unsigned char	*insert_first_third(unsigned char *dest, t_arr **arr, int i)
{
	unsigned char	*item;
	size_t			size_of;
	size_t			len;

	item = (*arr)->item;
	len = i + 1;
	size_of = (*arr)->size_of;
	ft_memcpy(dest, item, len * size_of);
	return (dest + len * size_of);
}

unsigned char	*insert_second_third(unsigned char *dest, t_arr **new)
{
	unsigned char	*item;
	size_t			size_of;
	size_t			len;

	item = (*new)->item;
	len = (*new)->len;
	size_of = (*new)->size_of;
	ft_memcpy(dest, item, len * size_of);
	return (dest + len * size_of);
}

unsigned char	*insert_third_third(unsigned char *dest, t_arr **arr, int i)
{
	unsigned char	*item;
	size_t			size_of;
	size_t			len;

	len = (*arr)->len - (i + 1);
	item = (unsigned char *)(*arr)->item + (i + 1) * (*arr)->size_of;
	size_of = (*arr)->size_of;
	ft_memcpy(dest, item, len * size_of);
	return (dest + len * size_of);
}

static unsigned char	*insert(t_arr **arr, t_arr **new, int i)
{
	unsigned char	*dest;
	unsigned char	*result;
	size_t			total;

	total = ((*arr)->len + (*new)->len) * (*new)->size_of;
	dest = malloc(total);
	if (!dest)
		return (NULL);
	result = dest;
	dest = insert_first_third(dest, arr, i);
	dest = insert_second_third(dest, new);
	dest = insert_third_third(dest, arr, i);
	free((*arr)->item);
	(*arr)->item = result;
	return ((*arr)->item);
}

/**
 * @brief Inserts a new array into an existing array after a specified index.
 *
 * Negative index can be used.
 *
 * @param arr Double pointer to the existing array structure.
 * @param new Double pointer to the new array structure to be inserted.
 * @param i Index at which the new array should be inserted.
 * @return t_arr* Pointer to the updated array structure, or NULL on failure.
 */
t_arr	*arr_insert(t_arr **arr, t_arr **new, int i)
{
	if (!arr)
		return (NULL);
	if (!new || !*new)
		return (*arr);
	if (!*arr)
	{
		*arr = *new;
		return (*arr);
	}
	if ((*arr)->size_of != (*new)->size_of)
		return (NULL);
	if (i > (int)(*arr)->len - 1 || i < -(int)(*arr)->len)
		return (NULL);
	if (i < 0)
		i = (*arr)->len + i;
	if (!insert(arr, new, i))
		return (NULL);
	(*arr)->len = (*arr)->len + (*new)->len;
	arr_clean(new, NULL);
	return (*arr);
}
