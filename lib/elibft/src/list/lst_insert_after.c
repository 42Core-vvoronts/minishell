/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_insert_after.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 08:35:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/12 12:13:29 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

//fully cleans src
//after: t_lnd *node
//complexity: 1
int	lst_insert_after(t_lst **dst, t_lnd *node, t_lst **src)
{
	t_lnd	*tmp;

	if (!dst || !src)
		return (FAIL);
	if (!*dst)
	{
		*dst = *src;
		return (SUCCESS);
	}
	(*dst)->len += (*src)->len;
	tmp = node->next;
	node->next = (*src)->head;
	(*src)->head->prev->next = tmp;
	tmp->prev = (*src)->head->prev;
	(*src)->head->prev = node;
	free(*src);
	*src = NULL;
	return (SUCCESS);
}
