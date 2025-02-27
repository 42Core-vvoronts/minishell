/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 06:25:06 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/27 10:28:08 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_directory(char *pathname)
{
	DIR	*dir;

	dir = opendir(pathname);
	if (dir)
	{
		closedir(dir);
		errno = EISDIR;
		return (true);
	}
	return (false);
}

char	*get_cmdname(void *node)
{
	return (((t_node *)node)->ctx->stash[0]);
}

bool	is_ambiguous(char **stash)
{
	return (ft_parrlen(stash));
}

void	restore_stdfd(int stdfd, t_node *node)
{
	if (stdfd == STDIN_FILENO)
		edup2(node->ctx->fdin, stdfd, node);
	else if (stdfd == STDOUT_FILENO)
		edup2(node->ctx->fdout, stdfd, node);
}
