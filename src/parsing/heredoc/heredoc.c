/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:28:07 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 01:32:59 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_pipe_content(t_pipe p)
{
	char c;

	while(read(p.read, &c, 1))
	{
		if (c == 4)
			break ;
		write(1, &c, 1);
	}
}

void	collect_heredoc(char *delim)
{
	char	*line;
	t_pipe	p;
	char	eot;

	// evaluate_node(node->left);
	// delim = pop_stash(node); //getfd here
	//delim remove quotes
	open_pipe(&p, NULL);
	eot = 4;
	while (1)
	{
		line = readline("> ");
		if (!line || is_eqlstr(line, delim))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, p.write);
		ft_putchar_fd('\n', p.write);
		free(line);
	}
	write(p.write, &eot, 1);
	dup2(p.read, STDIN_FILENO);
	char **envp = malloc(sizeof(char *));
	execve("/bin/cat", envp, envp);
	print_pipe_content(p);
}
