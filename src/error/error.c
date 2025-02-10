/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:58:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 10:50:14 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		error(-1, node->ctx, (t_m){strerror(errno)});
}
pid_t	efork(t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(-1, node->ctx, (t_m){strerror(errno)});
	return (pid);
}

int	eopen(char *pathname, int flags, int mode, t_node *node)
{
	int	fd;

	fd = open(pathname, flags, mode, node);
	if (fd == ERROR)
	{
		free(pathname);
		error(-1, node->ctx, (t_m){strerror(errno)});
	}
	return (fd);
}

void	eexecve(char *pathname, char **argv, char **envp)
{
	if (execve(pathname, argv, envp) == ERROR)
	{
		free(pathname);
		ft_parrclean(&argv);
		ft_parrclean(&envp);
		error(-1, NULL, (t_m){strerror(errno)});
		exit(1);
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

int	allclean(t_node *node, int mode)
{
	t_ctx	*ctx;
	int		exitcode;

	if (mode == 1)
	{
		ft_parrclean(&(node->ctx->envp));
		ft_parrclean(&(node->ctx->stash));
	}
	ctx = node->ctx;
	clean_tree(node->ctx->head);
	exitcode = ctx->exitcode;
	free(ctx);
	return (exitcode);
}

//it duplicates char *arg
void	add_msg(char *arg, t_node *node)
{
	size_t	i;
	char **result;

	i = ft_parrlen(node->ctx->msg);
	result = ft_calloc(i + 2, sizeof(char *));
	if (!result)
		error(-1, node->ctx, (t_m){strerror(errno)});
	arg = ft_strdup(arg);
	if (!arg)
		error(-1, node->ctx, (t_m){strerror(errno)});
	i = 0;
	while (node->ctx->msg && (node->ctx->msg)[i])
	{
		result[i] = (node->ctx->msg)[i];
		i++;
	}
	result[i] = arg;
	free(node->ctx->msg);
	node->ctx->msg = result;
}

void error(int exitcode, t_ctx *ctx, t_m msg)
{
	puterr(PROGRAMM);
	while (*msg)
	{
		if (*msg > (char *)TOK)
		{
			puterr(" `");
			puterr(*msg - TOK);
			puterr("\'");
			msg++;
			continue ;
		}
		puterr(": ");
		puterr(*msg);
		msg++;
	}
	puterr("\n");
	if (exitcode < 0)
	{
		allclean(ctx->head, FULL);
		exit(exitcode);
	}
	else
		set_exitcode(ctx->head, exitcode);
	return ;
	// if (error == PERMISSION_DENIED)
	// {
	// 	// puterr(get_cmdname(data));
	// 	// puterr(": ");
	// 	perror("");
	// 	if (terminate == true)
	// 	{
	// 		//clean here mem and fd
	// 		exit(1);
	// 	}
	// 	set_exitcode(data, 1);
	// }
	// else if (error == NOT_EXECUTABLE)
	// {
	// 	// puterr(get_cmdname(data));
	// 	// puterr(": ");
	// 	perror("");
	// 	exit(126);
	// }
	// else if (error == CMD_NOT_FOUND)
	// {
	// 	// puterr(get_cmdname(data));
	// 	// puterr(": ");
	// 	puterr("command not found\n");
	// 	exit(127);
	// }
	// else if (error == AMBIGUOUS_REDIR)
	// {
	// 	// puterr(": ");
	// 	//bash: $VAR: ambiguous redirect
	// 	puterr("ambiguous redirect\n");
	// 	set_exitcode(data, 1);
	// }
	// else if (error == NOT_VALID_IDENTIFIER)
	// {
	// 	puterr("export: ");
	// 	puterr(((t_node *)data)->ctx->error[0]);
	// 	puterr(": ");
	// 	puterr("not a valid identifier\n");
	// 	set_exitcode(data, 1);
	// }
	// else if (error == SYNTAX_ERROR)
	// {
	// 	// bash: syntax error near unexpected token `('
	// 	set_exitcode(data, 2);
	// }
	// else if (error == BUILTIN_MISUSE)
	// {
	// 	// ivan@fb32f8d82885:~$ cd -fddv
	// 	// bash: cd: -f: invalid option
	// 	// cd: usage: cd [-L|[-P [-e]] [-@]] [dir]
	// 	set_exitcode(data, 2);
	// }
	// else if (error == NON_NUMERIC_EXIT)
	// {
	// 	puterr("exit: ");
	// 	puterr(((t_node *)data)->ctx->error[0]);
	// 	puterr(": ");
	// 	puterr("numeric argument required\n");
	// 	// allclean(node);
	// 	exit(1);
	// }
	// else if (error == TOO_MANY_ARG_EXIT)
	// {
	// 	puterr("exit: ");
	// 	puterr("too many arguments\n");
	// 	// allclean(node);
	// 	set_exitcode(data, 1);
	// }
	// else if (error == TOO_MANY_ARG_CD)
	// {
	// 	puterr("cd: ");
	// 	puterr("too many arguments\n");
	// 	// allclean(node);
	// 	set_exitcode(data, 1);
	// }
	// else if (error == ERRNO_CD)
	// {
	// 	puterr("cd: ");
	// 	//print hint here
	// 	perror("");
	// 	set_exitcode(data, 1);
	// }
	// else if (error == OLDPWD_NOT_SET_CD)
	// {
	// 	puterr("cd: ");
	// 	puterr("OLDPWD not set\n");
	// 	set_exitcode(data, 1);
	// }
	// else if (error == HOME_NOT_SET_CD)
	// {
	// 	puterr("cd: ");
	// 	puterr("HOME not set\n");
	// 	set_exitcode(data, 1);
	// }
	// else
	// {
	// 	perror("");
	// 	exit(1);
	// }
}
