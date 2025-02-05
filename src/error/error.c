/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:58:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 08:28:47 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	puterr(char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
}

// static char *get_msg(t_error error)
// {
// 	if (error == MALLOC)
// 		return ("malloc: allocation failed");
// 	else if (error == CMD_NOT_FOUND)
// 		return ("command not found");
// 	else if (error == FILE_NOT_FOUND)
// 		return ("No such file or directory");
// 	return ("");
// }
pid_t	efork(t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(node, STRUCT_NODE, FORK_FAIL);
	return (pid);
}

void	eexecve(char *pathname, t_node *node)
{
	if (execve(pathname, node->ctx->stash, node->ctx->envp) == ERROR)
	{
		free(pathname);
		error(node, STRUCT_NODE, EXECVE_FAIL);
	}
}
void error(void *data, t_datatype datatype, t_error error)
{
	(void)datatype;
	(void)error;

	ft_putstr_fd("bash: ", STDERR_FILENO);
	if (error == FILE_NOT_FOUND)
	{
		puterr(get_cmdname(data));
		puterr(": ");
		puterr("No such file or directory\n");
		//clean here mem and fd
		exit(1);
	}
	else if (error == PERMISSION_DENIED)
	{
		puterr(get_cmdname(data));
		puterr(": ");
		perror("");
		exit(1);
	}
	else if (error == CMD_NOT_FOUND)
	{
		puterr(get_cmdname(data));
		puterr(": ");
		puterr("command not found\n");
		exit(1);

	}
	else if (error == GENERIC)
	{
		perror("");
		exit(1);
	}
}
