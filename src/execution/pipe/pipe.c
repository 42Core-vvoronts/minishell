/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:06:41 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/09 10:07:13 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static	void	process_left_child(t_pipe p, pid_t pid, t_node *node)
{
	if (pid == 0)
	{
		// kill(getpid(), SIGSTOP);
		edup2(p.write, STDOUT_FILENO, node);
		close_pipe(&p);
		evaluate(node->left);
		run_cmd(node);
		exit(allclean(node));
	}
	edup2(p.read, STDIN_FILENO, node);
	close_pipe(&p);
}

static	void	process_right_child(pid_t pid, t_node *node)
{
	pid = fork();
	if (pid == 0)
	{
		// kill(getpid(), SIGSTOP);
		evaluate(node->right);
		run_cmd(node);
		exit(allclean(node));
	}
	else if (pid > 0)
	{
		node->ctx->exitcode = get_exitcode(pid);
	}
}

void	process_pipe(t_node *node)
{
	t_pipe	p;
	pid_t	pid;

	open_pipe(&p, node);
	pid = efork(node);
	process_left_child(p, pid, node);
	if (node->right->type != PIPE)
	{
		process_right_child(pid, node);
		return ;
	}
	evaluate(node->right);
	return ;
}
