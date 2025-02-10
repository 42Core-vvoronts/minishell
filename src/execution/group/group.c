/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:08:52 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 12:40:22 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_group(t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		evaluate(node->left);
		return ;
	}
	else if (pid > 0)
	{
		node->ctx->exitcode = get_exitcode(pid);
		return ;
	}
}
