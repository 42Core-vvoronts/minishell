/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:23:16 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/24 08:19:03 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	is_valid(char *pathname, t_node *node)
{
	if (!pathname || is_ambiguous(node->ctx->stash))
	{
		error(1, node->ctx, (t_m){node->left->token, AMBIG_REDIR}); //exit(1): bash: $VAR: ambiguous redirect
		ft_parrclean(&(node->ctx->stash));
		return (false);
	}
	else if (!is_exist(pathname))
	{
		error(1, node->ctx, (t_m){pathname, strerror(errno)}); //exit(1); bash: f100: No such file or directory
		return (false);
	}
	else if (is_directory(pathname))
	{
		error(1, node->ctx, (t_m){pathname, IS_DIR}); //exit(1): bash: f2: Permission denied
		return (false);
	}
	else if (!is_readable(pathname))
	{
		error(1, node->ctx, (t_m){pathname, strerror(errno)}); //exit(1): bash: f2: Permission denied
		return (false);
	}
	return (true);
}

void	process_redir_in(t_node *node)
{
	int		fd;
	char	*pathname;

	evaluate(node->left);
	pathname = pop_stash(node);
	if (is_valid(pathname, node))
	{
		fd = eopen(pathname, O_RDONLY, 0777, node);
		edup2(fd, STDIN_FILENO, node);
		close(fd);
		evaluate(node->right);
	}
	restore_stdfd(STDIN_FILENO, node);
	free(pathname);
}
