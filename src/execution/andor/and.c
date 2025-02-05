/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:09:28 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 02:14:57 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	process_and(t_node	*node)
{
	int	exitcode;

	(void)exitcode;

	evaluate_node(node->left);
	if (node->ctx->exitcode == EXIT_SUCCESS)
	{
		evaluate_node(node->right);
		run_cmd(node);
	}
	return ;
}
