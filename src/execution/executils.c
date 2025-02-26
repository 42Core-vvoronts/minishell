/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 06:25:06 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/26 04:07:56 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_exist(char *pathname)
{
	return (!access(pathname, F_OK));
}

bool	is_readable(char *pathname)
{
	return (!access(pathname, R_OK));
}

bool	is_writable(char *pathname)
{
	return (!access(pathname, W_OK));
}

bool is_directory(char *pathname)
{
    DIR *dir;

	dir = opendir(pathname);
    if (dir)
    {
        closedir(dir);
		errno = EISDIR;
        return (true);
    }
    return (false);
}


bool is_executable(char *pathname)
{
	return (!access(pathname, F_OK | X_OK));
}

bool is_pathname(char *cmd)
{
	return (ft_strchr(cmd, '/'));
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
