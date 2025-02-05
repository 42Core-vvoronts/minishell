/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:07:37 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 11:24:24 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static	void	run_bin(t_node *node)
{
	pid_t	pid;
	char	*pathname;

	pid = efork(node);
	if (pid == 0)
	{
		pathname = get_pathname(node);
		eexecve(pathname, node);
	}
	else if (pid > 0)
		node->ctx->exitcode = get_exitcode(pid);
}

static	bool	run_builtin(t_node *node)
{
	if (is_eqlstr("echo", get_cmdname(node)))
		run_echo(node);
	else if (is_eqlstr("cd", get_cmdname(node)))
		run_cd(node);
	else if (is_eqlstr("pwd", get_cmdname(node)))
		run_pwd(node);
	else if (is_eqlstr("export", get_cmdname(node)))
		run_export(node);
	else if (is_eqlstr("unset", get_cmdname(node)))
		run_unset(node);
	else if (is_eqlstr("env", get_cmdname(node)))
		run_env(node);
	else if (is_eqlstr("exit", get_cmdname(node)))
		run_exit(node);
	else
		return (false);
	return (true);
}

void	run_cmd(t_node *node)
{
	if (node->ctx->exitcode != EXIT_SUCCESS)
	{
		ft_parrclean(&(node->ctx->stash));
		return ;
	}
	prepare_argv(node);
	if (run_builtin(node))
		return;
	run_bin(node);
}
