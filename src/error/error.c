/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:58:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/06 11:50:16 by ipetrov          ###   ########.fr       */
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
void	edup2(int oldfd, int newfd, t_node *node)
{
	if (dup2(oldfd, newfd) == ERROR)
		error(node, STRUCT_NODE, DUP_FAIL, true);
}
pid_t	efork(t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(node, STRUCT_NODE, FORK_FAIL, true);
	return (pid);
}

int	eopen(char *pathname, int flags, int mode, t_node *node)
{
	int	fd;

	fd = open(pathname, flags, mode, node);
	if (fd == ERROR)
	{
		free(pathname);
		error(node, STRUCT_NODE, OPEN_FAIL, true);
	}
	return (fd);
}

void	eexecve(char *pathname, t_node *node)
{
	if (execve(pathname, node->ctx->stash, node->ctx->envp) == ERROR)
	{
		free(pathname);
		error(node, STRUCT_NODE, EXECVE_FAIL, true);
	}
}

static	void	clean_tree(t_node *node)
{
	if (node == NULL)
		return ;
	clean_tree(node->left);
	clean_tree(node->right);
	free(node);
}
int	allclean(t_node *node)
{
	t_ctx	*ctx;
	int		exitcode;

	free(node->ctx->ttyname);
	free(node->ctx->fds);
	ft_parrclean(&(node->ctx->envp));
	ft_parrclean(&(node->ctx->stash));
	ctx = node->ctx;
	clean_tree(node->ctx->head);
	exitcode = ctx->exitcode;
	free(ctx);
	return (exitcode);
}
// void	terminate()

void error(void *data, t_datatype datatype, int error, bool terminate)
{
	(void)datatype;
	(void)error;

	ft_putstr_fd("bash: ", STDERR_FILENO);
	if (error == FILE_NOT_FOUND)
	{
		// puterr(get_cmdname(data));
		// puterr(": ");
		puterr("No such file or directory\n");
		if (terminate == true)
		{
			//clean here mem and fd
			exit(1);
		}
		set_exitcode(data, 1);
	}
	else if (error == PERMISSION_DENIED)
	{
		// puterr(get_cmdname(data));
		// puterr(": ");
		perror("");
		if (terminate == true)
		{
			//clean here mem and fd
			exit(1);
		}
		set_exitcode(data, 1);
	}
	else if (error == NOT_EXECUTABLE)
	{
		// puterr(get_cmdname(data));
		// puterr(": ");
		perror("");
		exit(126);
	}
	else if (error == CMD_NOT_FOUND)
	{
		// puterr(get_cmdname(data));
		// puterr(": ");
		puterr("command not found\n");
		exit(127);
	}
	else if (error == AMBIGUOUS_REDIR)
	{
		// puterr(": ");
		puterr("ambiguous redirect\n");
		set_exitcode(data, 1);
	}
	else if (error == NOT_VALID_IDENTIFIER)
	{
		puterr("export: ");
		puterr(((t_node *)data)->ctx->hint);
		puterr(": ");
		puterr("not a valid identifier\n");
		set_exitcode(data, 1);
	}
	else if (error == SYNTAX_ERROR)
	{
		// bash: syntax error near unexpected token `('
		set_exitcode(data, 2);
	}
	else if (error == BUILTIN_MISUSE)
	{
		// ivan@fb32f8d82885:~$ cd -fddv
		// bash: cd: -f: invalid option
		// cd: usage: cd [-L|[-P [-e]] [-@]] [dir]
		set_exitcode(data, 2);
	}
	else
	{
		perror("");
		exit(1);
	}
}
