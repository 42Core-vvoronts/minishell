/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parrclean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:03:12 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/24 07:58:43 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

//use &arr
void	ft_parrclean(void *arr)
{
	void	**a;

	if (!arr)
		return ;
	a = (void **)*(void **)arr;
	while (*(void **)arr && *a)
		free(*a++);
	free(*(void **)arr);
	*(void **)arr = NULL;
}
