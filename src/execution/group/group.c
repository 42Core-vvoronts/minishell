/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:08:52 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 04:15:47 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	process_group(t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		evaluate(node->right);
		return ;
	}
	else if (pid > 0)
	{
		node->ctx->exitcode = get_exitcode(pid); //last_child
		//set $? using node->ctx->exitcode use export builtin for that
		return ;
	}
}
