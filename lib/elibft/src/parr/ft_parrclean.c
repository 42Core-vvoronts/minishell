/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parrclean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:03:12 by ipetrov           #+#    #+#             */
/*   Updated: 2024/11/26 20:04:40 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

long long	ft_parrclean(int code, void (*del)(void *), void *arr1, void *arr2)
{
	void	**a1;
	void	**a2;

	a1 = (void **)arr1;
	while (arr1 && *a1)
		del(*a1++);
	free(arr1);
	a2 = (void **)arr2;
	while (arr2 && *a2)
		del(*a2++);
	free(arr2);
	return ((long long)code);
}
