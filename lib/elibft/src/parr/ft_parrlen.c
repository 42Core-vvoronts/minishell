/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:12:35 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/02 15:51:37 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Calculates the length of a NULL-terminated array of pointers.
 *
 * @param arr The NULL-terminated array of pointers.
 * @return The number of elements in the array, excluding the NULL terminator.
 */
size_t	ft_parrlen(void *arr)
{
	void	**mem;
	void	**arr2;

	if (!arr)
		return (0);
	arr2 = (void **)arr;
	mem = arr2;
	while (*arr2)
		arr2++;
	return (arr2 - mem);
}
