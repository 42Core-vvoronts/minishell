/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:23:38 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/09 10:07:13 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	bool	is_valid(char *pathname, t_node *node)
{
	if (is_ambiguous(pathname))
	{
		error(node, STRUCT_NODE, AMBIGUOUS_REDIR, false);
		return (false);
	}
	else if (!is_writable(pathname))
	{
		error(node, STRUCT_NODE, PERMISSION_DENIED, false);
		return (false);
	}
	return (true);
}

void	process_redir_out(t_node *node)
{
	int		fd;
	char	*pathname;

	evaluate(node->left);
	pathname = pop_arg(node);
	if (is_valid(pathname, node))
	{
		fd = eopen(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0666, node);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		evaluate(node->right);
	}
	free(pathname);
}
