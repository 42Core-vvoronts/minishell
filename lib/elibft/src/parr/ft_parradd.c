/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parradd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:14:53 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/12 07:07:12 by ipetrov          ###   ########.fr       */
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

	len = ft_parrlen(arr);
	result = (void **)malloc((len + 2) * sizeof(void *));
	if (!result)
		return (NULL);
	mem = result;
	a = (void **)arr;
	while (arr && *a)
		*result++ = *a++;
	*result++ = item;
	*result = NULL;
	free(arr);
	return ((void *)mem);
}
