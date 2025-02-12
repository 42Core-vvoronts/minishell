/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:06:41 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/12 04:09:41 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	process_left_child(t_node *node)
{
	pid_t	pid;
	t_pipe	p;

	open_pipe(&p, node);
	pid = efork(node);
	if (pid == 0)
	{
		// kill(getpid(), SIGSTOP);
		edup2(p.write, STDOUT_FILENO, node);
		close_pipe(&p);
		evaluate(node);
		exit(allclean(node, 1));
	}
	edup2(p.read, STDIN_FILENO, node);
	close_pipe(&p);
}

static	void	process_right_child(t_node *node)
{
	pid_t	pid;

	if (node->type == PIPE)
	{
		evaluate(node);
		return ;
	}
	pid = efork(node);
	if (pid == 0)
	{
		// kill(getpid(), SIGSTOP);
		evaluate(node);
		exit(allclean(node, 1));
	}
	restore_stdfd(STDIN_FILENO, node);
	node->ctx->exitcode = get_exitcode(pid);
}

void	process_pipe(t_node *node)
{
	process_left_child(node->left);
	process_right_child(node->right);
}
