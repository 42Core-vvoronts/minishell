/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:44:23 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/09 12:34:17 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_redir_heredoc(t_node *node)
{
	char	*content;
	t_pipe	p;

	evaluate(node->left);
	content = pop_arg(node);
	open_pipe(&p, node);
	ft_putstr_fd(content, p.write);
	dup2(p.read, STDIN_FILENO);
	close_pipe(&p);
}
