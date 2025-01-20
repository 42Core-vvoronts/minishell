/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:59:17 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/11 16:46:10 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

//complexity: n
t_lnd	*lst_get(t_lst **lst, int i)
{
	t_lnd	*result;

	if (!lst || !*lst)
		return (NULL);
	result = (*lst)->head;
	if (i < 0)
	{
		while (i++)
			result = result->prev;
	}
	else if (i > 0)
	{
		while (i--)
			result = result->next;
	}
	return (result);
}
