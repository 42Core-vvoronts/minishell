/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:28:07 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/17 17:35:35 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_delimeter(char **lexeme, t_ctx *ctx)
{
	char	*start;
	char	*end;
	char	*delim;

	skip_blanks(lexeme);
	start = *lexeme;
	end = start;
	while (*end && !is_blank(end))
		end++;
	delim = ft_strndup(start, end - start);
	if (!delim)
		error(-1, ctx, (t_m){strerror(errno), NULL});
	*lexeme = end;
	return delim;
}

void	tokenize_content(char *delim, t_tok **tokens, t_tok **current, t_ctx *ctx)
{
	char	*content;
	char	*line;
	char	*tmp;
	t_tok	*new;

	if (!delim)
		error(2, ctx, (t_m){"syntax error near unexpected token `newline'"});
	content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line || is_eqlstr(line, delim))
		{
			free(line);
			break;
		}
		tmp = content;
		content = ft_strjoin(content, line);
		free(tmp);
		free(line);
	}
	new = init_token(content, ft_strlen(content), ctx);
	add_token(new, tokens, current);
}

void	tokenize_heredoc(char **lexeme, t_tok **tokens, t_tok **current, t_ctx *ctx)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start + 1;
	new = init_token(start, end - start + 1, ctx);
	add_token(new, tokens, current);
	*lexeme = end + 1;
	tokenize_content(get_delimeter(lexeme, ctx), tokens, current, ctx);
}
