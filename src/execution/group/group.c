/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:08:52 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/11 06:26:28 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_group(t_node *node)
{
	pid_t	pid;

	pid = efork(node);
	if (pid == 0)
	{
		evaluate(node->left);
		exit(allclean(node, 1));
		return ;
	}
	else if (pid > 0)
	{
		node->ctx->exitcode = get_exitcode(pid);
		return ;
	}
}
