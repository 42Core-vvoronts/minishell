/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:23:16 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/09 12:34:36 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	is_valid(char *pathname, t_node *node)
{
	if (is_ambiguous(pathname))
	{
		error(node, STRUCT_NODE, AMBIGUOUS_REDIR, false);
		return (false);
	}
	else if (!is_exist(pathname))
	{
		error(node, STRUCT_NODE, FILE_NOT_FOUND, false);
		return (false);
	}
	else if (!is_readable(pathname))
	{
		error(node, STRUCT_NODE, PERMISSION_DENIED, false);
		return (false);
	}
	return (true);
}

void	process_redir_in(t_node *node)
{
	int		fd;
	char	*pathname;

	evaluate(node->left);
	pathname = pop_arg(node);
	if (is_valid(pathname, node))
	{
		fd = eopen(pathname, O_RDONLY, 0777, node);
		edup2(fd, STDIN_FILENO, node);
		close(fd);
		evaluate(node->right);
	}
	free(pathname);
}
