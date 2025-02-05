/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:07:37 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 08:56:25 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	run_bin(char *pathname, t_node *node)
{
	pid_t	pid;

	pid = efork(node);
	if (pid == 0)
		eexecve(pathname, node);
	else if (pid > 0)
		node->ctx->exitcode = get_exitcode(pid);
}

bool	run_builtin(t_node *node)
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
	char	*pathname;

	prepare_argv(node);
	if (run_builtin(node))
		return;
	pathname = get_pathname(node);
	run_bin(pathname, node);
}
