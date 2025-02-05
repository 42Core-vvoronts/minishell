/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_after.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:23:22 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/11 16:47:40 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

//add after index
//after: t_lnd *node
//complexity: 1
int	lst_add_after(t_lst **dst, t_lnd *node, void *item)
{
	t_lst	*src;

	if (!dst)
		return (FAIL);
	if (!lst_new(&src, item))
		return (FAIL);
	if (!*dst)
	{
		*dst = src;
		return (SUCCESS);
	}
	lst_insert_after(dst, node, &src);
	return (SUCCESS);
}
