/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:46:00 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:39:36 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

static unsigned char	*pop(t_arr **arr, int i)
{
	unsigned char	*dest;
	unsigned char	*result;
	void			*item;
	size_t			len;
	size_t			size_of;

	len = (*arr)->len;
	size_of = (*arr)->size_of;
	dest = malloc((len - 1) * size_of);
	if (!dest)
		return (NULL);
	item = (*arr)->item;
	size_of = (*arr)->size_of;
	result = dest;
	ft_memcpy(dest, item, i * size_of);
	dest = dest + (i * size_of);
	item = (unsigned char *)item + (i + 1) * size_of;
	ft_memcpy(dest, item, (len - (i + 1)) * size_of);
	free((*arr)->item);
	(*arr)->item = result;
	return ((*arr)->item);
}

/**
 * @brief Extracts an item from the array at
 * a specified index and updates the array.
 *
 * @param arr Double pointer to the array structure.
 * @param i Index of the item to be extracted.
 * @return void* Pointer to the extracted item, or NULL on failure.
 */
void	*arr_extract(t_arr **arr, int i)
{
	void	*item;

	if (!arr || !(*arr)->item || !(*arr)->len || !(*arr)->size_of)
		return (NULL);
	item = malloc((*arr)->size_of);
	if (!item)
		return (NULL);
	if (i > (int)(*arr)->len - 1 || i < -(int)(*arr)->len)
		return (NULL);
	if (i < 0)
		i = (*arr)->len + i;
	ft_memcpy(item, (unsigned char *)(*arr)->item + i * (*arr)->size_of, \
	(*arr)->size_of);
	if (!pop(arr, i))
		return (NULL);
	(*arr)->len -= 1;
	return (item);
}
