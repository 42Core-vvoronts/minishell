/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:44:23 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 11:51:07 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_redir_heredoc(t_node *node)
{
	(void)node;
	char	*line;
	char	*delim;
	t_pipe	p;
	t_file	*fl;

	evaluate_node(node->left);
	delim = pop_arg(node); //getfd here
	open_pipe(&p, node);
	while (1)
	{
		ft_printf("> ");
		get_next_line(STDIN_FILENO, &line, &fl);
		line[ft_strlen(line) - 1] = '\0';
		if (is_eqlstr(line, delim))
		{
			free(line);
			break ;
		}
		line[ft_strlen(line)] = '\n';
		ft_putstr_fd(line, p.write);
		free(line);
	}
	dup2(p.read, STDIN_FILENO);
	close_pipe(&p);
	free(fl);
}
