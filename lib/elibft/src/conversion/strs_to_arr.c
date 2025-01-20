/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:49:48 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:44:20 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

//it mallocs copy of *parr
//it doesnt clean passed void **parr to support stack
t_arr	*strs_to_arr(t_arr **arr, char **strs)
{
	if (!arr || !strs)
		return (NULL);
	strs = ft_strdups(strs);
	if (!strs)
		return (NULL);
	if (!arr_new(arr, strs, sizeof(char *), ft_parrlen(strs)))
		return ((void *)ft_parrclean(0, free, strs, NULL));
	return (*arr);
}
