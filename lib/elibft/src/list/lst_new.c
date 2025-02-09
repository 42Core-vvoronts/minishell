/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 08:31:24 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/11 17:43:26 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

//complexity: 1
int	lst_new(t_lst **lst, void *item)
{
	t_lnd	*node;

	if (!lst)
		return (FAIL);
	node = malloc(sizeof(t_lnd));
	if (!node)
		return (FAIL);
	node->item = item;
	node->next = node;
	node->prev = node;
	*lst = malloc(sizeof(t_lst));
	if (!*lst)
		return (free(node), FAIL);
	(*lst)->head = node;
	(*lst)->param = NULL;
	(*lst)->len = 1;
	return (SUCCESS);
}
