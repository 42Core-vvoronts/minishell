/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:10:13 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 11:31:49 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_argument(t_node *node)
{
	char *arg;

	//expand $var and expand *
	arg = ft_strdup(node->token);
	if (!arg)
		error(-1, node->ctx, (t_m){strerror(errno), NULL});
	add_stash(arg, node);
	if (node->left)
		evaluate(node->left);
	else
		run_cmd(node);
}
