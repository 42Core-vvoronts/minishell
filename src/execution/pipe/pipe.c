/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:06:41 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 01:06:57 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	process_pipe(t_node *node)
{
	t_pipe	p;
	pid_t	pid;

	open_pipe(&p);
	pid = fork(); //check for fail
	if (pid == 0)
	{
		// kill(getpid(), SIGSTOP);
		dup2(p.write, STDOUT_FILENO);
		close_pipe(&p);
		evaluate_node(node->left);
		run_cmd(node); // execve() here all what i have in a stash
	}
	dup2(p.read, STDIN_FILENO);
	close_pipe(&p);
	if (node->right->type != PIPE)
	{
		pid = fork();
		if (pid == 0)
		{
			// kill(getpid(), SIGSTOP);
			evaluate_node(node->right);
			run_cmd(node);
			// execeve() here and in init fork of not NULL;
			// or fork() and then exit(wait())
		}
		else if (pid > 0)
		{
			// fork();??
			node->ctx->exitcode = get_exitcode(pid); //waitpid()?? skips all other pids?
			//collect all other children exitcode here as well
		}
		return ;
	}
	evaluate_node(node->right);
	return ;
}
