/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:55:19 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:47:19 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

static char	**clean(void **result, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(result[i++]);
	free(result);
	return (NULL);
}

void	*ft_alloc(void *result, size_t size_of, size_t depth, size_t *spans)
{
	void	**arr;
	size_t	i;

	(void)depth;
	arr = malloc(sizeof(void *) * spans[0]);
	if (!arr)
		return (FAIL);
	i = 0;
	while (i < spans[0])
	{
		arr[i] = malloc(size_of * spans[1]);
		if (!arr[i])
			return (clean(arr, i));
		i++;
	}
	*(void **)result = arr;
	return (*(void **)result);
}
