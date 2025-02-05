/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:07:37 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 06:36:39 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void run_cmd(t_node *node)
{
	char	*pathname;

	prepare_argv(node);
	pathname = get_pathname(node);
	if (execve(pathname, node->ctx->stash, node->ctx->envp) == ERROR)
	{
		free(pathname);
		error(node, STRUCT_NODE, EXECVE_FAIL);
	}
	// and clean collected fd
}
