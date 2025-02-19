/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:44:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 12:37:51 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	is_valid(char *pathname, t_node *node)
{
	if (is_ambiguous(pathname))
	{
		error(1, node->ctx, (t_m){node->left->token, strerror(errno)}); //exit(1): bash: $VAR: ambiguous redirect
		return (false);
	}
	else if (is_exist(pathname) && !is_writable(pathname))
	{
		error(1, node->ctx, (t_m){pathname, strerror(errno)}); //exit(1): bash: f2: Permission denied
		return (false);
	}
	return (true);
}

void	process_redir_append(t_node *node)
{
	int		fd;
	char	*pathname;

	evaluate(node->left);
	pathname = pop_stash(node);
	if (is_valid(pathname, node))
	{
		fd = eopen(pathname, O_WRONLY | O_APPEND | O_CREAT, 0666, node);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		evaluate(node->right);
	}
	restore_stdfd(STDOUT_FILENO, node);
	free(pathname);
}
