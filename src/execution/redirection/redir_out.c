/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:23:38 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/27 10:23:04 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	is_valid(char *pathname, t_node *node, int *fd)
{
	if (!pathname || is_ambiguous(node->ctx->stash))
	{
		error(1, node->ctx, (t_m){node->left->token, AMBIG_REDIR});
		ft_parrclean(&(node->ctx->stash));
		return (false);
	}
	else if ((is_exist(pathname) && !is_writable(pathname)))
	{
		error(1, node->ctx, (t_m){pathname, strerror(errno)});
		return (false);
	}
	else if (is_directory(pathname))
	{
		error(1, node->ctx, (t_m){pathname, IS_DIR});
		return (false);
	}
	*fd = eopen(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0666, node);
	if (*fd == ERROR)
		return (false);
	return (true);
}

void	process_redir_out(t_node *node)
{
	int		fd;
	char	*pathname;

	evaluate(node->left);
	pathname = pop_stash(node);
	if (is_valid(pathname, node, &fd))
	{
		free(pathname);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		evaluate(node->right);
		restore_stdfd(STDOUT_FILENO, node);
	}
	else
		free(pathname);
}
