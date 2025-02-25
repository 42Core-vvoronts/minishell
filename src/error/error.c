/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:58:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/25 06:20:19 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		error(1, node->ctx, (t_m){strerror(errno)});
	free(pathname);
	return (fd);
}

void	eexecve(char *pathname, t_node *node)
{
	int		exitcode;
	char	**argv;
	char	**envp;

	argv = node->ctx->stash;
	envp = node->ctx->envp;
	exitcode = node->ctx->exitcode;
	allclean(node, 0);
	setup_signals(IS_BINARY, node->ctx);
	if (!pathname)
		;
	else if (execve(pathname, argv, envp) == ERROR)
		error(-1, NULL, (t_m){strerror(errno)});
	free(pathname);
	ft_parrclean(&argv);
	ft_parrclean(&envp);
	exit(exitcode);
}

/**
 * @brief Print error message and exit
 *
 * @param exitcode The exit code
 * @param ctx The context
 * @param msg The message, (t_m){} is a struct with a message
 *
 * @note Usage: error(-1, node->ctx, (t_m){strerror(errno)});
 * error(127, node->ctx, (t_m){node->ctx->stash[0], FILE_NOT_FOUND});
 *
 */
void error(int exitcode, t_ctx *ctx, t_m msg)
{
	puterr(PROGRAMM);
	while (*msg)
	{
		puterr(": ");
		if (*msg > (char *)TOK)
		{
			puterr("`");
			puterr(*msg - TOK);
			puterr("\'");
			msg++;
			continue ;
		}
		puterr(*msg);
		msg++;
	}
	puterr("\n");
	if (exitcode < 0)
	{
		if (ctx)
			allclean(ctx->head, FULL);
		exit(exitcode);
	}
	else
		ctx->exitcode = exitcode;
	return ;
}
