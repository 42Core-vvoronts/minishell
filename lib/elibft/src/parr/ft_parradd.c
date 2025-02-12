/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parradd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:14:53 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/12 07:40:11 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

//it doesnot strdup void*item it just attachs
void	*ft_parradd(void *arr, void *item)
{
	size_t	len;
	void	**result;
	void	**mem;
	void	**a;

	a = (void **)arr;
	if (!arr)
	{
		a = malloc(sizeof(void *));
		if (!a)
			return (NULL);
		*a = NULL;
	}
	len = ft_parrlen(a);
	result = (void **)malloc((len + 2) * sizeof(void *));
	if (!result)
		return (NULL);
	mem = result;
	len = 0;
	while (a && a[len])
		*result++ = a[len++];
	*result++ = item;
	*result = NULL;
	free(a);
	return ((void *)mem);
}
