/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:25:51 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/11 16:40:34 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

//complexity: n
int	lst_iter(t_lst **lst, int (*f)(t_lst **, t_lnd *, void *), void *param)
{
	size_t	len;
	t_lnd	*node;
	int		status;

	if (!lst || !*lst || !f)
		return (FAIL);
	len = (*lst)->len;
	node = lst_get(lst, 0);
	while (len--)
	{
		status = f(lst, node, param);
		if (status == STOP)
			return (SUCCESS);
		if (status == ERROR)
			return (FAIL);
		node = node->next;
	}
	return (SUCCESS);
}
