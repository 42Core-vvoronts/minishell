/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:28:07 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/23 13:57:43 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_delimeter(char **lexeme, t_ctx *ctx)
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
		error(-1, ctx, (t_m){strerror(errno)});
	*lexeme = end;
	return delim;
}

static char *ft_strjoin_nl(char *content, char *line, t_ctx *ctx)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(line, "\n");
	if (!tmp)
	{
		free(content);
		free(line);
		error(-1, ctx, (t_m){strerror(errno)});
	}
	free(line);
	if (!content)
		return (tmp);
	tmp2 = content;
	content = ft_strjoin(content, tmp);
	if (!content)
	{
		free(tmp);
		free(tmp2);
		error(-1, ctx, (t_m){strerror(errno)});
	}
	free(tmp);
	free(tmp2);
	return (content);
}

static void	tokenize_content(char *delim, t_ctx *ctx, t_tok **tokens, t_tok **current)
{
	char	*content;
	char	*line;
	t_tok	*new;
	int 	sigflag;

	if (!delim)
		error(2, ctx, (t_m){"syntax error near unexpected token 'newline'"});
	content = NULL;
	new = NULL;
	sigflag = 0;
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			sigflag = 1;
			break ; //if signal do not make token just return NULL or false
		}
		if (!line || is_eqlstr(line, delim))
		{
			if (!line)
				error(0, ctx, (t_m){"warning: here-document delimited by end-of-file wanted", delim + TOK});
			free(line);
			break ;
		}
		content = ft_strjoin_nl(content, line, ctx);
	}
	if (sigflag)
	{
		t_node node;
		node.ctx = ctx;
		restore_stdfd(STDIN_FILENO, &node);
		free(content);
		current = NULL;
		return ;
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
	tokenize_content(get_delimeter(lexeme, ctx), ctx, tokens, current);
}
