/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:36:48 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/11 16:58:48 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

static int	plug(void *param)
{
	(void)param;
	return (SUCCESS);
}

static int	clean(t_lst **lst, t_lnd *node, void *f)
{
	int	(*func)(void *);

	(void)lst;
	func = (int (*)(void *))f;
	func(node->item);
	free(node);
	return (CONTINUE);
}

//complexity: n
int	lst_clean(t_lst **lst, int (*f)(void *))
{
	if (!lst)
		return (SUCCESS);
	if (!f)
		f = plug;
	lst_iter(lst, clean, f);
	free(*lst);
	*lst = NULL;
	return (SUCCESS);
}
