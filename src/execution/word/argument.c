/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:10:13 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 01:34:20 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_argument(t_node *node)
{
	char *arg;

	//expand $var and expand *
	arg = ft_strdup(node->token);
	if (!arg)
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	add_stash(arg, node);
	if (node->left)
		evaluate(node->left);
	else
		run_cmd(node);
}
