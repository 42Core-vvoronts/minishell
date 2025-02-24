/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 06:25:06 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/23 10:27:24 by ipetrov          ###   ########.fr       */
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


bool	is_ambiguous(char *pathname)
{
	return (ft_strchr(pathname, ' '));
}

void	restore_stdfd(int stdfd, t_node *node)
{
	int fd;

	fd = eopen(node->ctx->ttyname, O_RDWR, 0777, node);
	edup2(fd, stdfd, node);
	if (fd != stdfd)
		close(fd);
}

